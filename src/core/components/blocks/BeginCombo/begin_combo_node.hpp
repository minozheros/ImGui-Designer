
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_node_editor.h>
#include <string>
#include "begin_combo_params.hpp"
#include "core/components/base/visual_block.hpp"

namespace ed = ax::NodeEditor;
namespace core
{
    class BeginComboNode : public VisualBlock
    {
    public:
        BeginComboNode(ed::NodeId id);
        ~BeginComboNode();

        void draw();
        void render() override { draw(); }
        ed::NodeId getId() const { return id_; }

    private:
        ed::NodeId id_;
        BeginComboParams params_;
        ed::PinId inputPinLabel_;
        ed::PinId inputPinPreview_;
        ed::PinId inputPinFlags_;
        ed::PinId outputPinReturn_;

        float prevNodeWidth_;

        void updateIO();
    };
}