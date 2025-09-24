#!/usr/bin/env python3
"""
Script to generate parameter structs for ImGui blocks.

This script reads ImGui function metadata from            # Use constructor without default value for complex types
        if ('ImGui' in t and not any(simple in t for simple in ['ImVec2', 'ImVec4', 'ImU32', 'ImS32', 'ImU64', 'ImS64', 'ImU16', 'ImS16', 'ImU8', 'ImS8', 'ImGuiID', 'ImGuiTableFlags', 'ImGuiTreeNodeFlags', 'ImGuiWindowFlags', 'ImGuiButtonFlags', 'ImGuiColorEditFlags', 'ImGuiCond', 'ImGuiDragDropFlags', 'ImGuiFocusedFlags', 'ImGuiHoveredFlags', 'ImGuiPopupFlags', 'ImGuiSelectableFlags', 'ImGuiTabBarFlags', 'ImGuiTabItemFlags', 'ImGuiTableColumnFlags', 'ImGuiTableRowFlags', 'ImGuiTreeNodeFlags'])) or '&' in p['type'] or '*' in p['type'] or ('const' in p['type'] and not ('ImVec2' in t or 'ImVec4' in t)):     # Use constructor without default value for complex types
        if ('ImGui' in t and not any(simple in t for simple in ['ImVec2', 'ImVec4', 'ImU32', 'ImS32', 'ImU64', 'ImS64', 'ImU16', 'ImS16', 'ImU8', 'ImS8', 'ImGuiID', 'ImGuiTableFlags', 'ImGuiTreeNodeFlags', 'ImGuiWindowFlags', 'ImGuiButtonFlags', 'ImGuiColorEditFlags', 'ImGuiCond', 'ImGuiDragDropFlags', 'ImGuiFocusedFlags', 'ImGuiHoveredFlags', 'ImGuiPopupFlags', 'ImGuiSelectableFlags', 'ImGuiTabBarFlags', 'ImGuiTabItemFlags', 'ImGuiTableColumnFlags', 'ImGuiTableRowFlags', 'ImGuiTreeNodeFlags'])) or '&' in p['type'] or '*' in p['type'] or ('const' in p['type'] and not ('ImVec2' in t or 'ImVec4' in t)):        elif 'ImGui' in t and ('Cond' in t or 'Flags' in t or 'Col' in t or 'StyleVar' in t or 'DataType' in t or 'Dir' in t or 'Key' in t or 'MouseButton' in t or 'TableBgTarget' in t):
                # Enum types - use appropriate default values
                if 'Dir' in t:
                    default_val = 'ImGuiDir_None'
                elif 'Key' in t:
                    default_val = 'ImGuiKey_None'
                elif 'MouseButton' in t:
                    default_val = 'ImGuiMouseButton_Left'
                elif 'TableBgTarget' in t:
                    default_val = 'ImGuiTableBgTarget_None'
                else:
                    # For other enums, use 0 as default
                    default_val = '0'SON file and generates
C++ struct definitions for each function's parameters, inheriting from
IParamsBase. Each struct contains unique_ptr<Parameter<T>> fields
for each parameter and a vector of IParameter* for aggregation.
"""

import os
import json

def snake_to_camel(snake_str):
    """Convert snake_case string to camelCase."""
    if not snake_str:
        return snake_str
    # Split by underscore and capitalize each part except the first
    parts = snake_str.split('_')
    return parts[0] + ''.join(word.capitalize() for word in parts[1:])

# Path to the JSON file containing ImGui function metadata
JSON_PATH = os.path.join(os.path.dirname(__file__), 'output', 'imgui_functions.json')
# Path to the params directory where all parameter structs are generated
PARAMS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'src', 'generated', 'params'))
# Path to the generated directory where README.md will be created
GENERATED_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'src', 'generated'))
# Path to the src directory where the stub file will be created
SRC_PARAMS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', 'src', 'core', 'components', 'blocks', 'params'))

def cpp_type(param):
    """
    Convert ImGui parameter type to C++ type for Parameter<T>.

    Normalizes types by removing & and * to avoid template issues,
    and handles special cases like const char* and void*.
    """
    t = param['type'].strip()
    n = param['name']
    # Special cases
    if 'const char' in t:
        t = 'std::string'
    elif 'void' in t:
        # Skip void parameters entirely
        t = 'void'
    elif '&' in t or '*' in t:
        # Skip reference and pointer parameters
        t = 'void'
    else:
        # Normalize types: remove & and * for simplicity in templates
        t = t.replace('&', '').replace('*', '').strip()
    # Convert parameter name to camelCase
    camel_name = snake_to_camel(n)
    return t, camel_name

def struct_name(func_name, func_index, functions):
    """Generate struct name from function name, handling overloads."""
    # Count how many functions with this name exist
    overload_count = sum(1 for f in functions if f['name'] == func_name)
    
    if overload_count == 1:
        return f"{func_name}Params"
    else:
        # Find the index of this function among overloads
        overload_index = sum(1 for f in functions[:func_index] if f['name'] == func_name)
        return f"{func_name}Params{overload_index + 1}"

def param_type_for(p):
    """
    Determine if a parameter is INPUT or OUTPUT based on heuristics.

    Pointer types with names like p_*, out_*, or ending with _out are considered outputs.
    """
    t = p['type']
    n = p['name']
    is_pointer = '*' in t
    is_output = (
        is_pointer and (
            n.startswith('p_') or n.startswith('out_') or n.endswith('_out') or 'output' in n.lower()
        )
    )
    return 'ParameterType::OUTPUT' if is_output else 'ParameterType::INPUT'

def write_param_struct(func, func_index, functions, output_file):
    """
    Generate and write the parameter struct for a given ImGui function to the output file.

    Creates a struct inheriting from IParamsBase with unique_ptr fields
    for parameters, initializes them in constructor, and aggregates into a vector.
    """
    struct = struct_name(func['name'], func_index, functions)
    params = func.get('params', [])
    print(f"  Processing function: {func['name']} with {len(params)} parameters")

    field_lines = []
    includes = []

    # Add return value if not void
    ret_type = func.get('return_type', 'void').strip()

    # Add parameter fields
    for p in params:
        t, n = cpp_type(p)
        if t == 'void':  # Skip void parameters
            continue
        field_lines.append(f"    std::unique_ptr<Parameter<{t}>> {n};")

    # Add return value field if not void
    if ret_type != 'void' and '&' not in ret_type and '*' not in ret_type:
        field_lines.append(f"    std::unique_ptr<Parameter<{ret_type}>> return_value;")

    # Build vector aggregator and constructor
    vector_lines = ["    std::vector<IParameter*> parameters;\n",
                    f"    {struct}() {{\n"]

    for p in params:
        t, n = cpp_type(p)
        if t == 'void':  # Skip void parameters
            continue
        # Use constructor without default value for complex types
        # Use constructor without default value for complex types
        if ('ImGui' in t and not any(simple in t for simple in ['ImVec2', 'ImVec4', 'ImU32', 'ImS32', 'ImU64', 'ImS64', 'ImU16', 'ImS16', 'ImU8', 'ImS8', 'ImGuiID', 'ImGuiTableBgTarget', 'ImGuiTableFlags', 'ImGuiSelectableFlags'])) or '&' in p['type'] or '*' in p['type'] or ('const' in p['type'] and not ('ImVec2' in t or 'ImVec4' in t)):
            vector_lines.append(f"        {n} = std::make_unique<Parameter<{t}>>( \"{n}\", {param_type_for(p)} );\n")
        else:
            # Provide default values based on type
            if 'const char*' in p['type'] or 'std::string' in t:
                default_val = '""'
            elif 'int' in t or 'float' in t or 'bool' in t or 'size_t' in t or 'ImU32' in t or 'ImS32' in t or 'ImU64' in t or 'ImS64' in t or 'ImU16' in t or 'ImS16' in t or 'ImU8' in t or 'ImS8' in t or 'ImGuiID' in t or 'ImGuiTableBgTarget' in t or 'double' in t:
                default_val = '0'
            elif 'ImVec2' in t or 'ImVec4' in t:
                default_val = f'{t.replace("const ", "").replace("const", "").strip()}()'
            elif 'ImGui' in t and ('Dir' in t or 'Key' in t or 'MouseButton' in t):
                # Enum types - use appropriate default values
                if 'Dir' in t:
                    default_val = 'ImGuiDir_None'
                elif 'Key' in t:
                    default_val = 'ImGuiKey_None'
                elif 'MouseButton' in t:
                    default_val = 'ImGuiMouseButton_Left'
                else:
                    # For other enums, use 0 as default
                    default_val = '0'
            else:
                default_val = '{}'
            vector_lines.append(f"        {n} = std::make_unique<Parameter<{t}>>( \"{n}\", {default_val}, {param_type_for(p)} );\n")
        vector_lines.append(f"        parameters.push_back({n}.get());\n")

    if ret_type != 'void' and '&' not in ret_type and '*' not in ret_type:
        # Use constructor without default value for complex return types
        if ('ImGui' in ret_type and not ('ImVec2' in ret_type or 'ImVec4' in ret_type)) or '&' in ret_type or '*' in ret_type or ('const' in ret_type and not ('ImVec2' in ret_type or 'ImVec4' in ret_type)):
            vector_lines.append(f"        return_value = std::make_unique<Parameter<{ret_type}>>( \"return_value\", ParameterType::RETURN );\n")
        else:
            if 'const char*' in ret_type or 'std::string' in ret_type:
                default_ret = '""'
            elif 'int' in ret_type or 'float' in ret_type or 'bool' in ret_type or 'size_t' in ret_type or 'ImU32' in ret_type or 'ImS32' in ret_type or 'ImU64' in ret_type or 'ImS64' in ret_type or 'ImU16' in ret_type or 'ImS16' in ret_type or 'ImU8' in ret_type or 'ImS8' in ret_type or 'double' in ret_type:
                default_ret = '0'
            elif 'ImVec2' in ret_type or 'ImVec4' in ret_type:
                default_ret = f'{ret_type.replace("const ", "").replace("const", "").strip()}()'
            elif 'ImGui' in ret_type and ('Cond' in ret_type or 'Flags' in ret_type or 'Col' in ret_type or 'StyleVar' in ret_type or 'DataType' in ret_type or 'Dir' in ret_type or 'Key' in ret_type or 'MouseButton' in ret_type or 'TableBgTarget' in ret_type):
                # Enum return types - use appropriate default values
                if 'Dir' in ret_type:
                    default_ret = 'ImGuiDir_None'
                elif 'Key' in ret_type:
                    default_ret = 'ImGuiKey_None'
                elif 'MouseButton' in ret_type:
                    default_ret = 'ImGuiMouseButton_Left'
                elif 'TableBgTarget' in ret_type:
                    default_ret = 'ImGuiTableBgTarget_None'
                else:
                    # For other enums, use 0 as default
                    default_ret = '0'
            else:
                default_ret = '{}'
            vector_lines.append(f"        return_value = std::make_unique<Parameter<{ret_type}>>( \"return_value\", {default_ret}, ParameterType::RETURN );\n")
        vector_lines.append(f"        parameters.push_back(return_value.get());\n")

    vector_lines.append("    }\n")
    vector_lines.append(f"    const std::vector<IParameter*>& getParameters() const override {{ return parameters; }}\n")

    fields = '\n'.join(field_lines) if field_lines else '    // No parameters\n'
    code = f"\n// Parameter struct for {func['name']}\nstruct {struct} : public IParamsBase {{\n{fields}\n\n" + ''.join(vector_lines) + "};\n"

    # Write to the output file
    output_file.write(code)

def create_readme(generated_dir):
    """Create a README.md file in the generated directory."""
    readme_path = os.path.join(generated_dir, 'README.md')
    readme_content = """# Generated Files Directory

⚠️ **DO NOT EDIT THESE FILES MANUALLY** ⚠️

This directory contains auto-generated source code files that are created by build scripts.
Any manual changes to these files will be **overwritten** during the next build.

## What are these files?

The files in this directory are automatically generated from:
- ImGui API definitions and function signatures
- Parameter type mappings and struct definitions
- Factory maps for node creation
- Enum mappings and type conversions

## How are they generated?

These files are created by Python scripts located in the `scripts/` directory:
- `generate_imgui_block_params.py` - Creates parameter structs for ImGui functions
- `generate_node_factory_map.py` - Creates factory mappings for node creation
- `generate_node_params_map.py` - Creates parameter mappings for nodes
- And other generation scripts...

The generation process is typically triggered during the CMake build process.

## If you need to modify these files:

1. **Do not edit the generated files directly**
2. Instead, modify the corresponding generation script in `scripts/`
3. Re-run the generation process (usually via `build.sh regenerate`)
4. The changes will be reflected in the generated files

## Directory Structure

- `maps/` - Factory and parameter mapping files
- `params/` - Parameter struct definitions for ImGui functions
- Other subdirectories contain additional generated code

---
*This README was auto-generated by `scripts/generate_imgui_block_params.py`*
"""
    
    with open(readme_path, 'w') as f:
        f.write(readme_content)
    
    print(f"Created README.md in {generated_dir}")

def main():
    """Main function to generate parameter structs for all ImGui functions."""
    print("Starting parameter struct generation...")
    
    # Create README.md in the generated directory
    create_readme(GENERATED_DIR)
    if not os.path.exists(JSON_PATH):
        print(f"Error: JSON file not found at {JSON_PATH}")
        return

    with open(JSON_PATH, 'r') as f:
        functions = json.load(f)

    print(f"Loaded {len(functions)} functions from {JSON_PATH}")

    # Ensure the params directory exists
    os.makedirs(PARAMS_DIR, exist_ok=True)

    # Generate all structs in one file
    output_file_path = os.path.join(PARAMS_DIR, 'ImGuiBlockParams.hpp')
    with open(output_file_path, 'w') as output_file:
        # Write header includes
        output_file.write("// This file is autogenerated by scripts/generate_imgui_block_params.py. Do not edit manually, but edit the respective scripts to reflect the needed changes!\n")
        output_file.write("#pragma once\n")
        output_file.write("#include <imgui.h>\n")
        output_file.write("#include <vector>\n")
        output_file.write("#include <memory>\n")
        output_file.write('#include "core/types/base/ParameterBase.hpp"\n')
        output_file.write('#include "core/types/interfaces/IParameter.hpp"\n')
        output_file.write('#include "core/types/interfaces/IParamsBase.hpp"\n')
        output_file.write('#include "core/types/Parameter.hpp"\n')
        output_file.write("\nnamespace core {\n")

        processed_count = 0
        for func_index, func in enumerate(functions):
            write_param_struct(func, func_index, functions, output_file)
            processed_count += 1

        output_file.write("\n} // namespace core\n")

    print(f"Parameter struct generation complete. Processed {processed_count} functions.")
    print(f"Generated single header file: {output_file_path}")

    # Create stub file in src directory
    os.makedirs(SRC_PARAMS_DIR, exist_ok=True)
    stub_file_path = os.path.join(SRC_PARAMS_DIR, 'ImGuiBlockParams.hpp')
    with open(stub_file_path, 'w') as stub_file:
        stub_file.write("// This file is autogenerated by scripts/generate_imgui_block_params.py. Do not edit manually, but edit the respective scripts to reflect the needed changes!\n")
        stub_file.write('#include "generated/params/ImGuiBlockParams.hpp"\n')

    print(f"Generated stub header file: {stub_file_path}")

if __name__ == '__main__':
    main()
