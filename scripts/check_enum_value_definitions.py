#!/usr/bin/env python3
"""
check_enum_value_definitions.py

Checks that all enum values in imgui_typedef_values.json are actually defined in the ImGui headers.
Prints warnings for any missing values and can be used by the generator script for filtering.
"""
import json
import sys
from pathlib import Path
import re

def collect_defined_symbols(imgui_src_dir):
    symbols = set()
    for path in Path(imgui_src_dir).rglob("*.h"):
        with open(path, 'r', encoding='utf-8', errors='ignore') as f:
            for line in f:
                # Match enum values and #define constants
                m = re.match(r'\s*(ImGui\w+),?', line)
                if m:
                    symbols.add(m.group(1))
                m = re.match(r'\s*#define\s+(ImGui\w+)', line)
                if m:
                    symbols.add(m.group(1))
    return symbols

def main():
    script_dir = Path(__file__).parent
    typedef_values_path = script_dir / "output" / "imgui_typedef_values.json"
    imgui_src_dir = Path("build/_deps/imgui-src")

    with open(typedef_values_path, 'r', encoding='utf-8') as f:
        typedef_values = json.load(f)

    defined_symbols = collect_defined_symbols(imgui_src_dir)
    missing = []
    for typedef, values in typedef_values.items():
        if not isinstance(values, list):
            continue
        for v in values:
            if v not in defined_symbols:
                print(f"WARNING: {v} (for {typedef}) is not defined in ImGui headers.")
                missing.append((typedef, v))
    if missing:
        print(f"Found {len(missing)} missing enum values.")
        sys.exit(1)
    else:
        print("All enum values are defined in ImGui headers.")
        sys.exit(0)

if __name__ == "__main__":
    main()
