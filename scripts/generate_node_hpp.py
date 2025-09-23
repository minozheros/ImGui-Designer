#!/usr/bin/env python3
"""
Generate a node .hpp file for ImGui-Designer from a params header.
Usage:
  ./scripts/generate_node_hpp.py <params_header.hpp> <NodeName>
Example:
  ./scripts/generate_node_hpp.py begin_combo_params.hpp BeginCombo
"""
import sys
from pathlib import Path
import re

def cpp_class(name):
    return ''.join(part.capitalize() for part in name.replace('-', '_').split('_')) + 'Node'

def main():
    if len(sys.argv) != 3:
        print("Usage: generate_node_hpp.py <params_header.hpp> <NodeName>")
        sys.exit(1)
    params_header = sys.argv[1]
    node_name = sys.argv[2]
    params_path = Path(params_header)
    if not params_path.exists():
        print(f"Params header not found: {params_header}")
        sys.exit(1)
    params_text = params_path.read_text()
    # Find struct name
    m = re.search(r'struct\s+(\w+)', params_text)
    if not m:
        print("Could not find struct name in params header.")
        sys.exit(1)
    params_struct = m.group(1)
    class_name = cpp_class(node_name)
    out = f'''#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>
#include <string>
#include "{params_path.name}"

namespace ed = ax::NodeEditor;

#include "core/components/base/visual_block.hpp"

class {class_name} : public VisualBlock {{
public:
    {class_name}(ed::NodeId id, const {params_struct} &params);
    ~{class_name}();

    void draw();
    void render() override {{ draw(); }}

    ed::NodeId getId() const {{ return id_; }}

private:
    ed::NodeId id_;
    {params_struct} params_;
    ed::PinId inputPinId_;
    ed::PinId outputPinId_;
}};
'''
    out_path = params_path.parent / f"{node_name.lower()}_node.hpp"
    out_path.write_text(out)
    print(f"Generated: {out_path}")

if __name__ == "__main__":
    main()
