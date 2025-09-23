#!/usr/bin/env python3
"""
Extract all unique parameter types from imgui_functions.json, noting if each is used as input, output, or both.
Output: parameter_types.json
"""
import json
from pathlib import Path
from collections import defaultdict
import re

input_path = Path('scripts/output/imgui_functions.json')
output_dir = Path('scripts/output')
output_dir.mkdir(parents=True, exist_ok=True)
output_path = output_dir / 'parameter_types.json'

type_usage = defaultdict(set)


with input_path.open() as f:
    functions = json.load(f)


def normalize_type(typ):
    # Remove const, pointer, reference, and default value, but preserve multi-word types
    typ = re.sub(r'\bconst\b', '', typ)
    typ = typ.replace('&', '').replace('*', '')
    typ = re.sub(r'\s*=.*', '', typ)  # Remove default value
    typ = re.sub(r'\s+', ' ', typ)
    return typ.strip()

for func in functions:
    params = func.get('params', [])
    for param in params:
        raw_typ = param.get('type', '').strip()
        name = param.get('name', '')
        norm_typ = normalize_type(raw_typ)
        is_pointer = '*' in raw_typ
        is_output = (
            is_pointer and (
                name.startswith('p_') or name.startswith('out_') or name.endswith('_out') or 'output' in name.lower()
            )
        )
        if is_output:
            type_usage[norm_typ].add('output')
        else:
            type_usage[norm_typ].add('input')

# Prepare output: list of dicts [{"type": ..., "usage": ["input", "output"]}]
result = []
for typ, usages in sorted(type_usage.items()):
    result.append({"type": typ, "usage": sorted(list(usages))})

with output_path.open('w') as f:
    json.dump(result, f, indent=2)

print(f"Wrote {output_path}")
