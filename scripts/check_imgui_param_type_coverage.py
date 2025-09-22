#!/usr/bin/env python3
"""
check_imgui_param_type_coverage.py

Checks that all parameter types used in imgui_functions.json are covered by the extracted enums, structs, and typedefs.
Prints a report of any missing types.
"""
import json
import sys
from pathlib import Path

def load_json(path):
    with open(path, 'r', encoding='utf-8') as f:
        return json.load(f)

def main():
    # Paths
    output_dir = Path(__file__).parent / "output"
    functions_path = output_dir / "imgui_functions.json"
    enums_path = output_dir / "imgui_enums.json"
    structs_path = output_dir / "imgui_structs.json"
    typedefs_path = output_dir / "imgui_typedefs.json"
    typedef_values_path = output_dir / "imgui_typedef_values.json"

    # Load data
    functions = load_json(functions_path)
    enums = load_json(enums_path)
    structs = load_json(structs_path)
    typedefs = load_json(typedefs_path)
    typedef_values = load_json(typedef_values_path)

    # Collect all parameter types used in functions
    param_types = set()
    for func in functions:
        for param in func.get("parameters", []):
            t = param.get("type")
            if t:
                param_types.add(t.strip())

    # Collect all known types
    known_types = set()
    known_types.update(e.get("name") for e in enums)
    # Structs: keys of the dict are struct names
    if isinstance(structs, dict):
        known_types.update(structs.keys())
    else:
        known_types.update(s.get("name") for s in structs)
    # Typedefs: keys of the dict are typedef names
    if isinstance(typedefs, dict):
        known_types.update(typedefs.keys())
    else:
        known_types.update(t.get("name") for t in typedefs)
    # Add typedef values (for typedefs that are enums)
    known_types.update(typedef_values.keys())

    # Add some built-in types that are always available
    builtin_types = {
        "int", "float", "double", "bool", "char", "void", "unsigned int", "size_t",
        "ImTextureID", "ImDrawIdx", "ImU32", "ImS16", "ImU16", "ImS32", "ImU64", "ImS64", "ImU8", "ImS8",
        "const char*", "char*", "const void*", "void*", "const ImWchar*", "ImWchar*", "ImWchar",
        "const ImU32*", "ImU32*", "const float*", "float*", "const int*", "int*", "const ImVec2*", "ImVec2*",
        "const ImVec4*", "ImVec4*", "const ImGuiID*", "ImGuiID*", "ImGuiID",
        "const ImS8*", "ImS8*", "const ImU8*", "ImU8*", "const ImS16*", "ImS16*", "const ImU16*", "ImU16*",
        "const ImS32*", "ImS32*", "const ImU32*", "ImU32*", "const ImS64*", "ImS64*", "const ImU64*", "ImU64*",
        "const bool*", "bool*", "const double*", "double*", "const size_t*", "size_t*",
    }
    known_types.update(builtin_types)

    # Find missing types
    missing_types = sorted(param_types - known_types)

    if missing_types:
        print("Missing parameter types (not found in enums, structs, typedefs, or builtins):")
        for t in missing_types:
            print(f"  - {t}")
        sys.exit(1)
    else:
        print("All parameter types are covered by extracted data.")
        sys.exit(0)

if __name__ == "__main__":
    main()
