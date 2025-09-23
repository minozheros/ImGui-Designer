import os
import json

# Path to the JSON file containing ImGui function metadata
JSON_PATH = os.path.join(os.path.dirname(__file__), 'output', 'imgui_functions.json')
# Path to the blocks directory where function folders are created
BLOCKS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/core/components/blocks'))

def cpp_type(param):
    # Compose C++ type from JSON param dict
    # Use the type as-is from JSON, including pointer and const
    t = param['type'].strip()
    n = param['name']
    # Remap string pointers to std::string
    if t in ('const char*', 'char*'):
        return f'std::string {n}'
    # If type is just 'const', treat as 'const <name>' (legacy fallback)
    if t == 'const':
        return f"const {n}"
    return f"{t} {n}" if n else t

def struct_name(func_name):
    return f"{func_name}Params"

def write_param_struct(func, dir_path):
    struct = struct_name(func['name'])
    params = func.get('params', [])
    if not params:
        fields = '    // No parameters\n'
        needs_string = False
    else:
        field_lines = []
        needs_string = False
        for p in params:
            t = p['type'].strip()
            if t in ('const char*', 'char*'):
                needs_string = True
            field_lines.append(f"    {cpp_type(p)};")
        fields = '\n'.join(field_lines)
    # Always include <imgui.h> for ImGui types, and <string> if needed
    includes = ["#pragma once", "#include <imgui.h>"]
    if needs_string:
        includes.append("#include <string>")
    code = '\n'.join(includes) + f"\n\nstruct {struct} {{\n{fields}\n}};\n"
    # File name: <function_name>_params.hpp, snake_case
    def camel_to_snake(name):
        import re
        s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
        return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()
    # Remove all *_params.hpp files in the directory first
    for fname in os.listdir(dir_path):
        if fname.endswith('_params.hpp') or fname == 'params.hpp':
            os.remove(os.path.join(dir_path, fname))
    file_base = camel_to_snake(func['name']) + '_params.hpp'
    file_path = os.path.join(dir_path, file_base)
    with open(file_path, 'w') as f:
        f.write(code)
    print(f"Created: {file_path}")

def main():
    with open(JSON_PATH, 'r') as f:
        functions = json.load(f)
    for func in functions:
        dir_path = os.path.join(BLOCKS_DIR, func['name'])
        if os.path.isdir(dir_path):
            write_param_struct(func, dir_path)

if __name__ == '__main__':
    main()
