import os
import json

# Path to the JSON file containing ImGui function metadata
JSON_PATH = os.path.join(os.path.dirname(__file__), 'output', 'imgui_functions.json')
# Path to the blocks directory where function folders will be created
BLOCKS_DIR = os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/core/components/blocks'))

def main():
    # Load ImGui function metadata
    with open(JSON_PATH, 'r') as f:
        functions = json.load(f)

    # Create a directory for each function
    for func in functions:
        func_name = func['name']
        dir_path = os.path.join(BLOCKS_DIR, func_name)
        os.makedirs(dir_path, exist_ok=True)
        print(f"Created directory: {dir_path}")

if __name__ == '__main__':
    main()
