#!/usr/bin/env python3
"""
extract_imgui_api_information.py


Scans imgui.h for API function signatures, relevant enums, structs/classes, typedefs, and public constants/macros, and outputs:
- imgui_functions.json: All API functions and their parameters
- imgui_enums.json: All enums used in API function signatures (with values)
- imgui_structs.json: All ImGui structs/classes with their public fields
- imgui_typedefs.json: All ImGui typedefs/aliases
- imgui_constants.json: All public ImGui constants/macros

Usage:
    python3 extract_imgui_api_information.py <imgui_h_path> <output_dir>

Example:
    python3 extract_imgui_api_information.py ../third_party/imgui/imgui.h scripts/
"""
import os
import re
import sys
import json
from pathlib import Path

def extract_api_functions(imgui_h):
    # Improved: support multi-line, default args, pointers, references, and ImGui namespace
    with open(imgui_h, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    # Find ImGui namespace block
    ns_match = re.search(r'namespace\s+ImGui\s*\{(.*?)^\}', content, re.DOTALL | re.MULTILINE)
    if not ns_match:
        print("Could not find ImGui namespace block.")
        return [], set()
    ns_content = ns_match.group(1)
    # Match IMGUI_API function declarations (multi-line, with or without default args)
    func_pattern = re.compile(r'IMGUI_API\s+([\w:<>:&*]+)\s+(\w+)\s*\(([^)]*)\)\s*;', re.MULTILINE)
    # Match: type (multi-word, with *, &, const, etc.) and name (last word)
    # This version ensures pointer/reference markers are part of the type
    param_pattern = re.compile(r'^(?P<type>.+?[*&]?)\s+(?P<name>\w+)(\s*=\s*[^,]+)?$')
    functions = []
    enums_used = set()
    seen_types = set()
    param_log_lines = []
    for m in func_pattern.finditer(ns_content):
        ret_type, func_name, params = m.groups()
        param_list = []
        detected_types = set()
        for p in params.split(','):
            p = p.strip()
            if not p or p == 'void':
                continue
            pm = param_pattern.match(p)
            if pm:
                # Remove extra spaces but preserve pointer/reference
                ptype = re.sub(r'\s+', ' ', pm.group('type')).strip()
                pname = pm.group('name') or ''
                param_list.append({'type': ptype, 'name': pname})
                if ptype.startswith('ImGui'):
                    enums_used.add(ptype)
                if ptype not in seen_types:
                    detected_types.add(ptype)
                    seen_types.add(ptype)
        if detected_types:
            param_str = ', '.join([p.strip() for p in params.split(',') if p.strip() and p.strip() != 'void'])
            param_log_lines.append(f"{ret_type} {func_name}({param_str})")
            # Add return parameter
            if ret_type.strip() != 'void':
                param_log_lines.append(f"  return: {ret_type}")
            # For each parameter, state input/output and type
            for param in param_list:
                # Heuristic: pointer types with names like p_*, out_*, or ending with _out are outputs
                is_pointer = '*' in param['type']
                name = param['name']
                is_output = (
                    is_pointer and (
                        name.startswith('p_') or name.startswith('out_') or name.endswith('_out') or 'output' in name.lower()
                    )
                )
                direction = 'output' if is_output else 'input'
                param_log_lines.append(f"  {direction}: {param['type']} {param['name']}")
            param_log_lines.append("")
        if ret_type.startswith('ImGui'):
            enums_used.add(ret_type)
        functions.append({'name': func_name, 'return_type': ret_type, 'params': param_list})
    # Write log to file
    output_dir = Path('scripts/output')
    output_dir.mkdir(parents=True, exist_ok=True)
    log_path = output_dir / 'parameters.txt'
    with log_path.open('w') as f:
        f.write('\n'.join(param_log_lines))
    return functions, enums_used

def extract_enum_definitions(imgui_h, relevant_enums):
    enum_pattern = re.compile(r'enum\s+(class|struct)?\s*(ImGui\w+)\s*\{([^}]*)\}', re.DOTALL)
    value_pattern = re.compile(r'\s*(\w+)\s*(=\s*[^,]+)?\s*,?')
    enums = {}
    with open(imgui_h, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    for match in enum_pattern.finditer(content):
        name = match.group(2)
        if name not in relevant_enums:
            continue
        body = match.group(3)
        values = []
        for val_match in value_pattern.finditer(body):
            val_name = val_match.group(1)
            if val_name and not val_name.startswith('//'):
                values.append(val_name)
        if values:
            enums[name] = values
    return enums

def extract_structs_and_classes(imgui_h):
    # Only extract ImGui* structs/classes and their public fields
    struct_pattern = re.compile(r'(struct|class)\s+(ImGui\w+)\s*\{([^}]*)\};', re.DOTALL)
    field_pattern = re.compile(r'\s*([\w:<>]+)\s+(\w+);')
    structs = {}
    with open(imgui_h, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    for match in struct_pattern.finditer(content):
        name = match.group(2)
        body = match.group(3)
        fields = []
        for field_match in field_pattern.finditer(body):
            ftype, fname = field_match.groups()
            fields.append({'type': ftype, 'name': fname})
        if fields:
            structs[name] = fields
    return structs

def extract_typedefs(imgui_h):
    typedef_pattern = re.compile(r'typedef\s+([\w:<>]+)\s+(ImGui\w+);')
    typedefs = {}
    with open(imgui_h, 'r', encoding='utf-8', errors='ignore') as f:
        for line in f:
            m = typedef_pattern.match(line.strip())
            if m:
                typedefs[m.group(2)] = m.group(1)
    return typedefs

def extract_constants_and_macros(imgui_h):
    # Extract #define ImGui* and const/static int ImGui* macros/constants
    define_pattern = re.compile(r'#define\s+(ImGui\w+_\w*)\s+(.+)')
    const_pattern = re.compile(r'(?:const|static const)\s+int\s+(ImGui\w+_\w*)\s*=\s*([^;]+);')
    constants = {}
    def scan_file(path):
        try:
            with open(path, 'r', encoding='utf-8', errors='ignore') as f:
                for line in f:
                    dm = define_pattern.match(line.strip())
                    if dm:
                        constants[dm.group(1)] = dm.group(2).strip()
                    cm = const_pattern.match(line.strip())
                    if cm:
                        constants[cm.group(1)] = cm.group(2).strip()
        except Exception as e:
            print(f"Warning: Could not scan {path}: {e}")
    # Scan all relevant files
    scan_file(imgui_h)
    # Try to scan imgui_internal.h and imgui.cpp if they exist in the same directory
    base_dir = os.path.dirname(imgui_h)
    for fname in ["imgui_internal.h", "imgui.cpp"]:
        fpath = os.path.join(base_dir, fname)
        if os.path.exists(fpath):
            scan_file(fpath)
    return constants

def main():
    default_output_dir = os.path.join('scripts', 'output')
    if len(sys.argv) == 1:
        print(f"No arguments provided. Using defaults: imgui.h -> {default_output_dir}")
        print("You must specify the path to imgui.h as the first argument if not using the default.")
        sys.exit(1)
    elif len(sys.argv) == 2:
        imgui_h = sys.argv[1]
        output_dir = default_output_dir
    elif len(sys.argv) == 3:
        imgui_h = sys.argv[1]
        output_dir = sys.argv[2]
    else:
        print("Usage: python3 extract_imgui_api_information.py <imgui_h_path> <output_dir>")
        sys.exit(1)
    Path(output_dir).mkdir(parents=True, exist_ok=True)


    functions, enums_used = extract_api_functions(imgui_h)
    with open(os.path.join(output_dir, 'imgui_functions.json'), 'w', encoding='utf-8') as f:
        json.dump(functions, f, indent=2)

    enums = extract_enum_definitions(imgui_h, enums_used)
    with open(os.path.join(output_dir, 'imgui_enums.json'), 'w', encoding='utf-8') as f:
        json.dump(enums, f, indent=2)

    structs = extract_structs_and_classes(imgui_h)
    with open(os.path.join(output_dir, 'imgui_structs.json'), 'w', encoding='utf-8') as f:
        json.dump(structs, f, indent=2)

    typedefs = extract_typedefs(imgui_h)
    with open(os.path.join(output_dir, 'imgui_typedefs.json'), 'w', encoding='utf-8') as f:
        json.dump(typedefs, f, indent=2)


    # constants = extract_constants_and_macros(imgui_h)
    # with open(os.path.join(output_dir, 'imgui_constants.json'), 'w', encoding='utf-8') as f:
    #     json.dump(constants, f, indent=2)

    print(f"Extracted {len(functions)} functions, {len(enums)} enums, {len(structs)} structs/classes, {len(typedefs)} typedefs from {imgui_h}")

if __name__ == "__main__":
    main()
