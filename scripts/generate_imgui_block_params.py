import os
import json

# Path to the JSON file containing ImGui function metadata
JSON_PATH = os.path.join(os.path.dirname(__file__), 'output', 'imgui_functions.json')
# Path to the blocks directory where function folders are created
BLOCKS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/core/components/blocks'))

def cpp_type(param):
    # Compose ParameterBase<T> type for struct field
    t = param['type'].strip()
    n = param['name']
    # Use the type as-is from JSON, including pointer and const
    return t, n

def struct_name(func_name):
    return f"{func_name}Params"

def write_param_struct(func, dir_path):
    struct = struct_name(func['name'])
    params = func.get('params', [])
    field_lines = []
    includes = [
        "#pragma once",
        "#include <imgui.h>",
        "#include <vector>",
        "#include <core/types/base/parameter_base.hpp>"
    ]
    # Add return value if not void
    ret_type = func.get('return_type', 'void').strip()
    # ParameterType mapping
    def param_type_for(p):
        # Heuristic: pointer types with names like p_*, out_*, or ending with _out are outputs
        t = p['type']
        n = p['name']
        is_pointer = '*' in t
        is_output = (
            is_pointer and (
                n.startswith('p_') or n.startswith('out_') or n.endswith('_out') or 'output' in n.lower()
            )
        )
        return 'ParameterType::OUTPUT' if is_output else 'ParameterType::INPUT'
    # Add parameter fields
    for p in params:
        t, n = cpp_type(p)
        field_lines.append(f"    ParameterBase<{t}> {n} = ParameterBase<{t}>(\"{n}\", {param_type_for(p)});")
    # Add return value field if not void
    if ret_type != 'void':
        field_lines.append(f"    ParameterBase<{ret_type}> return_value = ParameterBase<{ret_type}>(\"return_value\", ParameterType::RETURN);")
    # Build vector aggregator
    vector_lines = ["    std::vector<core::IParameterBase*> params;\n",
                    f"    {struct}() {{\n"]
    for p in params:
        _, n = cpp_type(p)
        vector_lines.append(f"        params.push_back(&{n});\n")
    if ret_type != 'void':
        vector_lines.append(f"        params.push_back(&return_value);\n")
    vector_lines.append("    }\n")

    fields = '\n'.join(field_lines) if field_lines else '    // No parameters\n'
    code = '\n'.join(includes) + f"\n\nnamespace core\n{{\nstruct {struct} {{\n{fields}\n\n" + ''.join(vector_lines) + f"}};\n}}\n"
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
