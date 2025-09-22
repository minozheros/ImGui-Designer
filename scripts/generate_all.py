import os
import yaml
import argparse
import shutil

BLOCKS_YAML = "scripts/blocks.yaml"
BLOCKS_DIR = "src/core/components/blocks/"
STUBS_DIR = "src/core/components/stubs/"
REPORT_FILE = "src/core/components/stubs/report_unimplemented_blocks.cpp"

# --- Utility Functions ---
def load_types():
    with open(BLOCKS_YAML) as f:
        data = yaml.safe_load(f)
    return data['types'], data.get('to_delete', [])

def header_exists(path):
    return os.path.exists(path)

def is_stub_file(path):
    if not os.path.exists(path):
        return False
    with open(path, 'r') as f:
        return 'static bool isStub()' in f.read()

# --- Stub Generation ---
def stub_block_content(classname, paramsname, folder):
    return f"""// Auto-generated stub for {classname}
#pragma once
#include \"core/components/base/parametric_visual_block.hpp\"
#include \"core/components/blocks/{folder}/params.hpp\"
class {classname} : public ParametricVisualBlock {{
public:
    {classname}(std::unique_ptr<{paramsname}> params) : ParametricVisualBlock(std::move(params)) {{}}
    static bool isStub() {{ return true; }}
    void render() override {{}}
}};
"""

def stub_params_content(paramsname):
    return f"""// Auto-generated stub for {paramsname}
#pragma once
#include \"core/components/blocks/params/block_params.hpp\"
struct {paramsname} : public BlockParams {{
    {paramsname}() {{}}
    static bool isStub() {{ return true; }}
    std::unique_ptr<BlockParams> clone() const override {{ return std::make_unique<{paramsname}>(*this); }}
}};
"""

def generate_stubs(types):
    os.makedirs(STUBS_DIR, exist_ok=True)
    unimplemented = []
    for t in types:
        folder = t['name']
        block = t['class']
        params = t['params']
        block_folder = os.path.join(BLOCKS_DIR, folder)
        os.makedirs(block_folder, exist_ok=True)
        block_header = os.path.join(block_folder, "block.hpp")
        params_header = os.path.join(block_folder, "params.hpp")
        stub_block_path = os.path.join(STUBS_DIR, f"{block.lower()}.hpp")
        stub_params_path = os.path.join(STUBS_DIR, f"{params.lower()}.hpp")

        # Only generate stub if real implementation does not exist
        if not header_exists(block_header):
            with open(stub_block_path, "w") as f:
                f.write(stub_block_content(block, params, folder))
            with open(stub_block_path, "r") as src, open(block_header, "w") as dst:
                dst.write(src.read())
            unimplemented.append(block)
        if not header_exists(params_header):
            with open(stub_params_path, "w") as f:
                f.write(stub_params_content(params))
            with open(stub_params_path, "r") as src, open(params_header, "w") as dst:
                dst.write(src.read())
            unimplemented.append(params)

    # Generate report
    with open(REPORT_FILE, "w") as f:
        f.write("// Auto-generated report of unimplemented blocks/params\n")
        f.write("#include <iostream>\nvoid reportUnimplementedBlocks() {\n")
        f.write('    std::cout << "Unimplemented blocks/params (stubs):\\n";\n')
        for name in unimplemented:
            f.write(f'    std::cout << " - {name} (stub)\\n";\n')
        f.write("}\n")
    print("Stub generation complete. See src/core/components/blocks/ and report_unimplemented_blocks.cpp.")

# --- Block Copy/Sync ---
def generate_blocks(types):
    # This can be extended to copy or sync block/param files as needed
    print("Block generation/sync not implemented in this template.")

# --- Registry/Enum Generation ---
def generate_registry(types):
    # This can be extended to generate registry and enum code as needed
    print("Registry/enum generation not implemented in this template.")

# --- Main CLI ---
def main():
    parser = argparse.ArgumentParser(description="Unified code generator for blocks, stubs, registry, etc.")
    parser.add_argument('--stubs', action='store_true', help='Generate stubs')
    parser.add_argument('--blocks', action='store_true', help='Generate blocks (not implemented)')
    parser.add_argument('--registry', action='store_true', help='Generate registry/enums (not implemented)')
    parser.add_argument('--all', action='store_true', help='Run all generators')
    args = parser.parse_args()

    types, to_delete = load_types()

    if args.all or args.stubs:
        generate_stubs(types)
    if args.all or args.blocks:
        generate_blocks(types)
    if args.all or args.registry:
        generate_registry(types)

if __name__ == '__main__':
    main()
