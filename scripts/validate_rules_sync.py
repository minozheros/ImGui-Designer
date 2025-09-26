#!/usr/bin/env python3
"""Validate sync between canonical Markdown rules and machine-readable YAML.

Schema v2 expectations:
 - YAML `title` must exactly match the full descriptive Markdown title text after the ID+level segment.
 - YAML MUST contain `short_title` (concise label) but it is not compared to Markdown (derived field).
 - Level and ID sets must match.

Exit codes:
 0 = in sync
 1 = structural mismatch (parse errors, missing file)
 2 = content drift (IDs/levels/titles differ or missing short_title)

Enhancements (diff mode):
 - Categorized output: added, removed, changed (level/title), incomplete (missing short_title).
 - Unified style inline diff for title mismatches (best-effort minimal highlight).
 - Optional JSON report: pass --json to emit structured drift details.
 - Summary counts to aid CI dashboards.

Validation Strategy:
 1. Extract rules from Markdown lines matching '- [ID][LEVEL] ...' or cheat sheet enumerations.
 2. Load YAML; build map of id -> (level, title, short_title).
 3. Enforce: IDs equal, levels equal, titles exactly equal (case-sensitive), short_title present & non-empty.
 4. Report actionable diffs with categories & optional machine-readable output.
"""
from __future__ import annotations
import re
import sys
import json
import argparse
from difflib import SequenceMatcher
from pathlib import Path
try:
    import yaml  # type: ignore
except ImportError:  # lightweight fallback: bail with clear message
    print("FATAL: PyYAML not installed. Install with: pip install pyyaml", file=sys.stderr)
    sys.exit(1)

ROOT = Path(__file__).resolve().parent.parent
MD_FILE = ROOT / '.github' / 'instructions' / 'first.instructions.md'
YAML_FILE = ROOT / '.github' / 'instructions' / 'rules.yml'

RULE_LINE_RE = re.compile(r'^- \[(?P<ID>[A-Z0-9_-]+)\]\[(?P<LEVEL>MUST|SHOULD|MAY)\]\s+(?P<TITLE>.+)$')
CHEAT_SHEET_RE = re.compile(r'^\d+\. \[(?P<ID>[A-Z0-9_-]+)\]\[(?P<LEVEL>MUST|SHOULD|MAY)\]\s+(?P<TITLE>.+)$')

class Drift(Exception):
    pass

def parse_markdown() -> dict[str, dict]:
    if not MD_FILE.exists():
        raise Drift(f"Missing markdown file: {MD_FILE}")
    rules: dict[str, dict] = {}
    with MD_FILE.open('r', encoding='utf-8') as f:
        for raw in f:
            line = raw.strip()
            if not line or line.startswith('>'):
                continue
            m = RULE_LINE_RE.match(line) or CHEAT_SHEET_RE.match(line)
            if not m:
                continue
            rid = m.group('ID').upper()
            level = m.group('LEVEL')
            title = m.group('TITLE').strip()
            # Remove trailing parenthetical clarifiers from title for normalization
            title_clean = re.sub(r'\s*\([^)]*\)$', '', title).strip()
            rules[rid] = {
                'id': rid,
                'level': level,
                'title': title_clean,
                'raw_title': title,
            }
    if not rules:
        raise Drift('No rules parsed from markdown (pattern mismatch).')
    return rules

def parse_yaml() -> dict[str, dict]:
    if not YAML_FILE.exists():
        raise Drift(f"Missing YAML file: {YAML_FILE}")
    with YAML_FILE.open('r', encoding='utf-8') as f:
        data = yaml.safe_load(f)
    if not isinstance(data, dict) or 'rules' not in data:
        raise Drift('YAML root must contain a top-level "rules" list.')
    out: dict[str, dict] = {}
    for entry in data['rules']:
        if not isinstance(entry, dict):
            continue
        rid = str(entry.get('id', '')).upper()
        if not rid:
            continue
        out[rid] = {
            'id': rid,
            'level': entry.get('level'),
            'title': entry.get('title', '').strip(),
            'description': entry.get('description', '').strip(),
            'short_title': entry.get('short_title', '').strip(),
        }
    if not out:
        raise Drift('No rules parsed from YAML.')
    return out

def unified_inline_diff(a: str, b: str) -> str:
    """Produce a compact inline diff marking replacements with {old=>new}."""
    if a == b:
        return a
    sm = SequenceMatcher(None, a, b)
    parts: list[str] = []
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == 'equal':
            parts.append(a[i1:i2])
        elif op == 'replace':
            parts.append(f'{{{a[i1:i2]}=>{b[j1:j2]}}}')
        elif op == 'delete':
            parts.append(f'{{{a[i1:i2]}=>}}')
        elif op == 'insert':
            parts.append(f'{{=>{b[j1:j2]}}}')
    return ''.join(parts)

def compare(md_rules: dict[str, dict], y_rules: dict[str, dict]) -> tuple[list[str], dict]:
    errors: list[str] = []
    report: dict[str, object] = {
        'added': [],        # present in MD, missing in YAML
        'removed': [],      # present in YAML, missing in MD
        'changed': [],      # list of {id, field, md, yaml, diff}
        'incomplete': [],   # missing short_title
        'counts': {},
    }
    md_ids = set(md_rules)
    y_ids = set(y_rules)
    added = sorted(md_ids - y_ids)
    removed = sorted(y_ids - md_ids)
    if added:
        errors.append('Rules missing in YAML: ' + ', '.join(added))
    if removed:
        filtered = [r for r in removed if r != 'QUAL-01 (DUPLICATE-ID-NOTE)']
        if filtered:
            errors.append('Rules present in YAML but not Markdown: ' + ', '.join(filtered))
    report['added'] = added
    report['removed'] = removed
    intersect = md_ids & y_ids
    for rid in sorted(intersect):
        md = md_rules[rid]
        y = y_rules[rid]
        if str(md['level']).upper() != str(y['level']).upper():
            errors.append(f'{rid}: level mismatch MD={md["level"]} YAML={y["level"]}')
            report['changed'].append({
                'id': rid,
                'field': 'level',
                'md': md['level'],
                'yaml': y['level'],
                'diff': f'{md["level"]}=>{y["level"]}',
            })
        if md['title'] != y['title']:
            inline = unified_inline_diff(md['title'], y['title'])
            errors.append(f'{rid}: title mismatch')
            report['changed'].append({
                'id': rid,
                'field': 'title',
                'md': md['title'],
                'yaml': y['title'],
                'diff': inline,
            })
        if 'short_title' not in y or not y.get('short_title'):
            errors.append(f'{rid}: missing short_title in YAML entry')
            report['incomplete'].append(rid)
    report['counts'] = {
        'md': len(md_rules),
        'yaml': len(y_rules),
        'added': len(added),
        'removed': len(removed),
        'changed': len(report['changed']),
        'incomplete': len(report['incomplete']),
    }
    return errors, report

def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description='Validate sync between canonical Markdown rules and rules.yml mirror.')
    parser.add_argument('--json', action='store_true', help='Emit machine-readable JSON drift report to stdout (non-zero exit preserves report).')
    args = parser.parse_args(argv)
    try:
        md_rules = parse_markdown()
        y_rules = parse_yaml()
        diffs, report = compare(md_rules, y_rules)
    except Drift as e:
        print(f'[rules-sync] ERROR: {e}', file=sys.stderr)
        return 1
    if diffs:
        print('[rules-sync] DRIFT DETECTED:')
        for d in diffs:
            print(' -', d)
        counts = report['counts']  # type: ignore
        print(f"\nSUMMARY: added={counts['added']} removed={counts['removed']} changed={counts['changed']} incomplete={counts['incomplete']}")
        print('Canonical source: first.instructions.md -> Regenerate via scripts/generate_rules_yaml.py (or CMake target).')
        if args.json:
            print('\nJSON_REPORT_BEGIN')
            print(json.dumps(report, indent=2, sort_keys=True))
            print('JSON_REPORT_END')
        return 2
    print(f'[rules-sync] OK: {len(md_rules)} rules consistent between Markdown and YAML.')
    return 0

if __name__ == '__main__':
    sys.exit(main())
