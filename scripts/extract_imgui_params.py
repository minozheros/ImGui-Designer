import re
import json
import sys
import os
from dotenv import load_dotenv

# Default path to imgui.h in the workspace
DEFAULT_IMGUI_H = os.path.join("build", "_deps", "imgui-src", "imgui.h")

# Load .env for output path
load_dotenv(dotenv_path='scripts/.env')
IMGUI_FUNCTIONS_JSON = os.getenv('IMGUI_FUNCTIONS_JSON', 'scripts/imgui_functions.json')

def parse_imgui_functions(header_path):
    with open(header_path, 'r', encoding='utf-8', errors='ignore') as f:
        code = f.read()

    # Match ImGui function declarations (not static, not inline, not template)
    pattern = re.compile(r'IMGUI_API\s+([\w:<>]+)\s+(\w+)\s*\(([^)]*)\)\s*;')
    functions = {}
    for ret_type, func_name, args in pattern.findall(code):
        # Parse arguments
        arg_list = []
        if args.strip():
            for arg in args.split(','):
                arg = arg.strip()
                if arg == 'void':
                    continue
                # Split type and name
                parts = arg.rsplit(' ', 1)
                if len(parts) == 2:
                    arg_type, arg_name = parts
                else:
                    arg_type, arg_name = parts[0], ''
                arg_list.append({'type': arg_type.strip(), 'name': arg_name.strip()})
        functions[func_name] = {
            'return_type': ret_type.strip(),
            'args': arg_list
        }
    return functions

if __name__ == '__main__':
    # Usage: python extract_imgui_params.py [imgui.h] [output.json]
    header_path = DEFAULT_IMGUI_H
    output_path = IMGUI_FUNCTIONS_JSON
    if len(sys.argv) >= 2:
        header_path = sys.argv[1]
    if len(sys.argv) >= 3:
        output_path = sys.argv[2]
    if not os.path.exists(header_path):
        print(f"imgui.h not found at {header_path}", file=sys.stderr)
        sys.exit(1)
    functions = parse_imgui_functions(header_path)
    with open(output_path, 'w') as f:
        json.dump(functions, f, indent=2)
    print(f"ImGui function signatures written to {output_path}")
import re
import json
import sys
import os
from dotenv import load_dotenv

# Default path to imgui.h in the workspace
DEFAULT_IMGUI_H = os.path.join("build", "_deps", "imgui-src", "imgui.h")

# Load .env for output path
load_dotenv(dotenv_path='scripts/.env')
IMGUI_FUNCTIONS_JSON = os.getenv('IMGUI_FUNCTIONS_JSON', 'scripts/imgui_functions.json')

def parse_imgui_functions(header_path):
    with open(header_path, 'r', encoding='utf-8', errors='ignore') as f:
        code = f.read()

    # Match ImGui function declarations (not static, not inline, not template)
    pattern = re.compile(r'IMGUI_API\s+([\w:<>]+)\s+(\w+)\s*\(([^)]*)\)\s*;')
    functions = {}
    for ret_type, func_name, args in pattern.findall(code):
        # Parse arguments
        arg_list = []
        if args.strip():
            for arg in args.split(','):
                arg = arg.strip()
                if arg == 'void':
                    continue
                # Split type and name
                parts = arg.rsplit(' ', 1)
                if len(parts) == 2:
                    arg_type, arg_name = parts
                else:
                    arg_type, arg_name = parts[0], ''
                arg_list.append({'type': arg_type.strip(), 'name': arg_name.strip()})
        functions[func_name] = {
            'return_type': ret_type.strip(),
            'args': arg_list
        }
    return functions

if __name__ == '__main__':
    # Usage: python extract_imgui_params.py [imgui.h] [output.json]
    header_path = DEFAULT_IMGUI_H
    output_path = IMGUI_FUNCTIONS_JSON
    if len(sys.argv) >= 2:
        header_path = sys.argv[1]
    if len(sys.argv) >= 3:
        output_path = sys.argv[2]
    if not os.path.exists(header_path):
        print(f"imgui.h not found at {header_path}", file=sys.stderr)
        sys.exit(1)
    functions = parse_imgui_functions(header_path)
    with open(output_path, 'w') as f:
        json.dump(functions, f, indent=2)
    print(f"ImGui function signatures written to {output_path}")
