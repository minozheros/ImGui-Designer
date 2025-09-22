#!/usr/bin/env python3
"""
scan_enums_and_generate_json_converters.py

Scans C++ header/source files for enum definitions and generates nlohmann::json
to_json/from_json converters for each enum found.

Usage:
    python3 scan_enums_and_generate_json_converters.py <source_dir> <output_header>

Example:
    python3 scan_enums_and_generate_json_converters.py ../src include/generated/enum_json_converters.hpp
"""
import os
import re
import sys
from pathlib import Path

def find_enum_definitions(source_dir):
    enum_pattern = re.compile(r'enum\s+(class|struct)?\s*(\w+)\s*:\s*\w+|enum\s+(class|struct)?\s*(\w+)')
    value_pattern = re.compile(r'\s*(\w+)\s*(=\s*[^,]+)?\s*,?')
    enums = []
    for root, _, files in os.walk(source_dir):
        for file in files:
            if file.endswith(('.hpp', '.h', '.cpp', '.cc', '.cxx')):
                path = os.path.join(root, file)
                with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                    content = f.read()
                for match in enum_pattern.finditer(content):
                    name = match.group(2) or match.group(4)
                    if not name:
                        continue
                    # Find the body of the enum
                    start = match.end()
                    brace_open = content.find('{', start)
                    brace_close = content.find('};', brace_open)
                    if brace_open == -1 or brace_close == -1:
                        continue
                    body = content[brace_open+1:brace_close]
                    values = []
                    for val_match in value_pattern.finditer(body):
                        val_name = val_match.group(1)
                        if val_name and not val_name.startswith('//'):
                            values.append(val_name)
                    if values:
                        enums.append((name, values))
    return enums

def generate_json_converters(enums):
    lines = [
        '// This file is auto-generated. Do not edit manually.',
        '#pragma once',
        '#include <nlohmann/json.hpp>',
        '',
    ]
    for enum_name, values in enums:
        lines.append(f'// nlohmann::json converters for {enum_name}')
        # to_json
        lines.append(f'inline void to_json(nlohmann::json& j, const {enum_name}& e) {{')
        lines.append('    switch(e) {')
        for val in values:
            lines.append(f'        case {enum_name}::{val}: j = "{val}"; break;')
        lines.append('        default: j = nullptr; break;')
        lines.append('    }')
        lines.append('}')
        # from_json
        lines.append(f'inline void from_json(const nlohmann::json& j, {enum_name}& e) {{')
        for val in values:
            lines.append(f'    if (j == "{val}") {{ e = {enum_name}::{val}; return; }}')
        lines.append('    throw std::invalid_argument("Invalid enum value for ' + enum_name + '");')
        lines.append('}')
        lines.append('')
    return '\n'.join(lines)

def main():
    default_source = os.path.join('src', 'core', 'types', 'enums')
    default_output = os.path.join('include', 'generated', 'enum_json_converters.hpp')
    if len(sys.argv) == 1:
        print(f"No arguments provided. Using defaults: {default_source} -> {default_output}")
        source_dir = default_source
        output_header = default_output
    elif len(sys.argv) == 3:
        source_dir = sys.argv[1]
        output_header = sys.argv[2]
    else:
        print("Usage: python3 scan_enums_and_generate_json_converters.py <source_dir> <output_header>")
        print(f"Or run with no arguments to use defaults: {default_source} -> {default_output}")
        sys.exit(1)
    enums = find_enum_definitions(source_dir)
    if not enums:
        print("No enums found.")
        sys.exit(0)
    code = generate_json_converters(enums)
    Path(output_header).parent.mkdir(parents=True, exist_ok=True)
    with open(output_header, 'w', encoding='utf-8') as f:
        f.write(code)
    print(f"Generated converters for {len(enums)} enums in {output_header}")

if __name__ == "__main__":
    main()
