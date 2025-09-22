import json
import yaml
import os
from dotenv import load_dotenv

# Load .env for IMGUI_FUNCTIONS_JSON
load_dotenv(dotenv_path='scripts/.env')
IMGUI_FUNCTIONS_JSON = os.getenv('IMGUI_FUNCTIONS_JSON', 'scripts/imgui_functions.json')

# Output path for blocks.yaml
def get_blocks_yaml_path():
    return 'scripts/blocks.yaml'

# Naming conventions for class and params
ndefault = lambda s: s[0].upper() + s[1:] if s else s
def func_to_block_name(func):
    return f"ImGui_{func}"
def func_to_class(func):
    return f"{ndefault(func)}Block"
def func_to_params(func):
    return f"{ndefault(func)}BlockParams"

def main():
    with open(IMGUI_FUNCTIONS_JSON) as f:
        functions = json.load(f)
    types = []
    for func in functions:
        # Only include ImGui widgets (heuristic: start with uppercase, skip internal/utility)
        if not func or not func[0].isupper():
            continue
        block_entry = {
            'name': func_to_block_name(func),
            'class': func_to_class(func),
            'params': func_to_params(func)
        }
        types.append(block_entry)
    blocks_yaml = {'types': types}
    with open(get_blocks_yaml_path(), 'w') as f:
        yaml.dump(blocks_yaml, f, sort_keys=False)
    print(f"blocks.yaml generated with {len(types)} entries.")

if __name__ == '__main__':
    main()
