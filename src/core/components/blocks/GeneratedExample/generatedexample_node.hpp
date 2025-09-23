#pragma once

#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>
#include <string>
#include "generatedexample_params.hpp"

namespace ed = ax::NodeEditor;

#include "core/components/base/visual_block.hpp"

class GeneratedexampleNode : public VisualBlock
{
public:
    GeneratedexampleNode(ed::NodeId id, const GeneratedexampleParams &params);
    ~GeneratedexampleNode();

    void draw();
    void render() override { draw(); }

    ed::NodeId getId() const { return id_; }

private:
    ed::NodeId id_;
    GeneratedexampleParams params_;
    ed::PinId inputPinId_;
    ed::PinId outputPinId_;
};
