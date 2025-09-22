#!/usr/bin/env python3
"""
scan_typedefs_and_collect_values.py

For each typedef int ImGuiXXX; in imgui_typedefs.json, scan ImGui source files for all matching ImGuiXXX_* values (from #define or const/static int).

Usage:
    python3 scan_typedefs_and_collect_values.py <typedefs_json> <imgui_dir> <output_json>

Example:
    python3 scan_typedefs_and_collect_values.py scripts/output/imgui_typedefs.json build/_deps/imgui-src scripts/output/imgui_typedef_values.json
"""
import os
import re
import sys
import json
from pathlib import Path

def scan_for_values(imgui_dir, typedefs):
    # Collect all ImGuiXXX types
    typedef_names = [k for k, v in typedefs.items() if k.startswith('ImGui')]
    # For each typedef, look for enum blocks like enum ImGuiCol_ { ... };
    enum_block_pattern = re.compile(r'enum\s+(ImGui\w+_)\s*\{([^}]*)\};', re.DOTALL)
    value_pattern = re.compile(r'\s*(ImGui\w+_\w+)')
    values = {name: [] for name in typedef_names}
    for root, _, files in os.walk(imgui_dir):
        for file in files:
            if file.endswith(('.h', '.hpp', '.cpp', '.c')):
                path = os.path.join(root, file)
                try:
                    with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                        content = f.read()
                    for match in enum_block_pattern.finditer(content):
                        enum_prefix = match.group(1)  # e.g., ImGuiCol_
                        body = match.group(2)
                        # Map enum ImGuiCol_ to typedef ImGuiCol
                        typedef_name = enum_prefix[:-1]  # Remove trailing _
                        if typedef_name in values:
                            for val_match in value_pattern.finditer(body):
                                val = val_match.group(1)
                                if val not in values[typedef_name]:
                                    values[typedef_name].append(val)
                except Exception as e:
                    print(f"Warning: Could not scan {path}: {e}")
    return values

def main():
    if len(sys.argv) != 4:
        print("Usage: python3 scan_typedefs_and_collect_values.py <typedefs_json> <imgui_dir> <output_json>")
        sys.exit(1)
    typedefs_json = sys.argv[1]
    imgui_dir = sys.argv[2]
    output_json = sys.argv[3]
    with open(typedefs_json, 'r', encoding='utf-8') as f:
        typedefs = json.load(f)
    values = scan_for_values(imgui_dir, typedefs)
    with open(output_json, 'w', encoding='utf-8') as f:
        json.dump(values, f, indent=2)
    print(f"Collected values for {len(values)} typedefs. Output: {output_json}")

if __name__ == "__main__":
    main()
