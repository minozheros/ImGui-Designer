#!/usr/bin/env python3
"""Generate rules.yml from the canonical first.instructions.md.

Schema (v2):
- id: RULE-ID (string)
- level: MUST|SHOULD|MAY
- title: full descriptive title text from Markdown (human-focused)
- short_title: condensed label (auto-derived)
- description: currently mirrors title (hook for future expansion)
- section: best-effort inferred from last seen markdown section header (## or ###)
- tags: derived from id prefix + section tokenization
- since_version: left blank (reserved for future manual population)

Derivations:
 short_title heuristics:
   * Start with title.
   * Remove trailing clarifiers in parentheses.
   * Collapse phrases to <= 6 words; keep strong nouns/verbs.
   * Strip punctuation/backticks.

Id / level detection uses existing patterns:
  - Cheat sheet and rule lines: '- [ID][LEVEL] ...'

This script OVERWRITES rules.yml.
"""
from __future__ import annotations
import re
import sys
import yaml  # type: ignore
import argparse
from pathlib import Path
from collections import OrderedDict

ROOT = Path(__file__).resolve().parent.parent
MD_FILE = ROOT / '.github' / 'instructions' / 'first.instructions.md'
OUT_FILE = ROOT / '.github' / 'instructions' / 'rules.yml'

RULE_RE = re.compile(r'^- \[(?P<id>[A-Z0-9_-]+)\]\[(?P<level>MUST|SHOULD|MAY)\]\s+(?P<title>.+)$')
CHEAT_RE = re.compile(r'^\d+\. \[(?P<id>[A-Z0-9_-]+)\]\[(?P<level>MUST|SHOULD|MAY)\]\s+(?P<title>.+)$')
SECTION_RE = re.compile(r'^(#{2,3})\s+(?P<sec>.+?)\s*$')

STOP_WORDS = {"the","a","an","and","or","of","to","for","on","in","at","by","via","be"}


def short_title(full: str) -> str:
    # Remove backticks & markdown emphasis
    txt = re.sub(r'[`*_]', '', full)
    # Remove parenthetical clarifiers at end
    txt = re.sub(r'\s*\([^)]*\)$', '', txt).strip()
    # Split into words
    words = re.split(r'\W+', txt)
    cleaned = [w for w in words if w]
    # Keep strong words first, drop most stop words beyond first position
    out = []
    for w in cleaned:
        lw = w.lower()
        if len(out) >= 6:
            break
        if lw in STOP_WORDS and len(out) > 0:
            continue
        out.append(w)
    if not out:
        out = cleaned[:6]
    return ' '.join(out)


def load_existing_since_versions() -> dict[str, str | None]:
    if not OUT_FILE.exists():
        return {}
    try:
        with OUT_FILE.open('r', encoding='utf-8') as f:
            data = yaml.safe_load(f)
        existing: dict[str, str | None] = {}
        if isinstance(data, dict) and isinstance(data.get('rules'), list):
            for r in data['rules']:
                if isinstance(r, dict) and 'id' in r:
                    existing[str(r['id']).upper()] = r.get('since_version')
        return existing
    except Exception:
        return {}

def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description='Generate rules.yml from canonical markdown with schema v2.')
    parser.add_argument('--baseline-version', default=None, help='Baseline version string to stamp into since_version where missing.')
    parser.add_argument('--force-baseline', action='store_true', help='Force overwrite of null since_version values even if file existed before.')
    args = parser.parse_args(argv)

    if not MD_FILE.exists():
        print(f'Canonical file missing: {MD_FILE}', file=sys.stderr)
        return 1
    current_section = None
    rules_map: "OrderedDict[str, dict]" = OrderedDict()
    existing_since = load_existing_since_versions()
    with MD_FILE.open('r', encoding='utf-8') as f:
        for raw in f:
            line = raw.rstrip('\n')
            sec = SECTION_RE.match(line.strip())
            if sec:
                current_section = sec.group('sec')
                continue
            stripped = line.strip()
            if not stripped or stripped.startswith('>'):
                continue
            m = RULE_RE.match(stripped) or CHEAT_RE.match(stripped)
            if not m:
                continue
            rid = m.group('id').upper()
            level = m.group('level')
            title = m.group('title').strip()
            st = short_title(title)
            section = current_section or "(unknown)"
            prefix = rid.split('-')[0]
            tags = sorted({prefix.lower(), *(w.lower() for w in re.findall(r'[A-Za-z]+', section)[:3])})
            prev_since = existing_since.get(rid)
            if args.force_baseline and args.baseline_version:
                since_version = args.baseline_version
            else:
                if prev_since and prev_since != 'null':
                    since_version = prev_since
                else:
                    since_version = args.baseline_version if args.baseline_version else None
            # Overwrite any earlier (cheat sheet) entry so later section phrasing & level win
            rules_map[rid] = {
                'id': rid,
                'level': level,
                'title': title,
                'short_title': st,
                'description': title,
                'section': section,
                'tags': tags,
                'since_version': since_version,
            }
    data = {
        'version': 2,
        'generated': True,
        'schema': 'rules-schema-v2',
        'rules': list(rules_map.values()),
    }
    OUT_FILE.parent.mkdir(parents=True, exist_ok=True)
    with OUT_FILE.open('w', encoding='utf-8') as f:
        yaml.safe_dump(data, f, sort_keys=False, width=100)
    print(f'Wrote {len(rules_map)} rules to {OUT_FILE}')
    return 0

if __name__ == '__main__':
    sys.exit(main())
