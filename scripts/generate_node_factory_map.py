
import os
import json
import re


BLOCKS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/core/components/blocks'))
JSON_PATH = os.path.join(os.path.dirname(__file__), 'output', 'imgui_functions.json')
MAPS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/core/types/maps'))
default_output = os.path.join(MAPS_DIR, 'node_factory_map.hpp')

def camel_to_snake(name):
    s1 = re.sub('(.)([A-Z][a-z]+)', r'\1_\2', name)
    return re.sub('([a-z0-9])([A-Z])', r'\1_\2', s1).lower()

def main(output_path=default_output):
    # Load all ImGui function names
    with open(JSON_PATH, 'r') as f:
        functions = json.load(f)
    node_map = {}
    includes = []
    for func in functions:
        name = func['name']
        class_name = f"{name}Node"
        block_dir = name
        node_hpp = os.path.join(BLOCKS_DIR, block_dir, f"{camel_to_snake(block_dir)}_node.hpp")
        if os.path.isfile(node_hpp):
            includes.append(f'#include "core/components/blocks/{block_dir}/{camel_to_snake(block_dir)}_node.hpp"')
        node_map[name] = class_name
    # Write C++ header with map
    with open(output_path, 'w') as f:
        f.write('#pragma once\n')
        f.write('// Auto-generated NodeCreatorFactory map\n')
        f.write('#include <string>\n#include <unordered_map>\n')
        for inc in includes:
            f.write(f'{inc}\n')
        f.write('\nstatic const std::unordered_map<std::string, std::string> NODE_CLASS_MAP = {\n')
        for block, class_name in node_map.items():
            f.write(f'    {{"{block}", "{class_name}"}},\n')
        f.write('};\n')
    print(f"Node factory map written to {output_path}")

if __name__ == "__main__":
    main()
