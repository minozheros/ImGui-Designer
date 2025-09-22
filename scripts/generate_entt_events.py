import json
import os
from dotenv import load_dotenv

# Load .env for IMGUI_FUNCTIONS_JSON
load_dotenv(dotenv_path='scripts/.env')
IMGUI_FUNCTIONS_JSON = os.getenv('IMGUI_FUNCTIONS_JSON', 'scripts/imgui_functions.json')
EVENTS_OUT = 'src/core/components/events/imgui_block_events.hpp'

# Heuristic: which param names are likely to be event-relevant?
RELEVANT_FIELDS = {'value', 'checked', 'selected', 'current_item', 'active', 'toggled', 'text', 'color', 'position', 'size'}

def ndefault(s):
    return s[0].upper() + s[1:] if s else s

def func_to_block_name(func):
    return f"{ndefault(func)}Block"

def func_to_event_struct(block_name, params):
    struct_name = f"{block_name}ChangedEvent"
    lines = [f"struct {struct_name} {{"]
    for param in params:
        if param['name'] in RELEVANT_FIELDS:
            # Map C types to safe C++ types
            t = param['type']
            if t in ('const char*', 'char*', 'char'): t = 'std::string'
            elif t == 'bool': t = 'bool'
            elif t.startswith('ImVec'): t = t  # e.g., ImVec2
            elif t.endswith('*'): t = 'void*'  # fallback for pointers
            lines.append(f"    {t} {param['name']};")
    lines.append("    entt::entity source;")
    lines.append("};\n")
    return '\n'.join(lines)

def main():
    with open(IMGUI_FUNCTIONS_JSON) as f:
        functions = json.load(f)
    out_lines = ["// Auto-generated EnTT event structs for ImGui blocks\n#pragma once\n#include <string>\n#include <entt/entity/entity.hpp>\n"]
    for func, info in functions.items():
        block_name = func_to_block_name(func)
        params = info['args']
        struct_code = func_to_event_struct(block_name, params)
        # Only output if there are relevant fields
        if 'entt::entity source;' not in struct_code or struct_code.count(';') == 1:
            continue
        out_lines.append(struct_code)
    os.makedirs(os.path.dirname(EVENTS_OUT), exist_ok=True)
    with open(EVENTS_OUT, 'w') as f:
        f.write('\n'.join(out_lines))
    print(f"EnTT event structs written to {EVENTS_OUT}")

if __name__ == '__main__':
    main()
