
#include "begin_combo_node.hpp"
#include <array>
#include <cstring>

namespace core
{
    constexpr int kMaxLabelLen = 128;
    constexpr int kMaxPreviewLen = 128;
    ed::PinId makePinId(ed::NodeId nodeId, int offset)
    {
        return ed::PinId(nodeId.Get() + offset);
    }

    BeginComboNode::BeginComboNode(ed::NodeId id)
        : id_(id),
          inputPinLabel_(makePinId(id, 1)),
          inputPinPreview_(makePinId(id, 2)),
          inputPinFlags_(makePinId(id, 3)),
          outputPinReturn_(makePinId(id, 4)),
          prevNodeWidth_(0.0f)
    {
        spdlog::info("BeginComboNode constructed, id: {}", id_.Get());
        setNodeId(id_);
        updateIO();
    }

    BeginComboNode::~BeginComboNode()
    {
        spdlog::info("BeginComboNode destroyed, id: {}", id_.Get());
    }

    void BeginComboNode::updateIO()
    {
        // Set up inputs and outputs using Value<T> from ParameterBase
        setInput("label", params_.label.value.value);
        setInput("preview_value", params_.preview_value.value.value);
        setInput("flags", params_.flags.value.value);
        setOutput("return_value", params_.return_value.value.value);
    }

    void BeginComboNode::draw()
    {
        spdlog::info("BeginComboNode::draw called, id: {}", id_.Get());
        ed::BeginNode(id_);

        ImGui::Text("BeginCombo");

        // Calculate column widths based on content
        float bulletSpace = 15.0f; // Estimate space for bullet indicator
        float inputWidth = std::max({ImGui::CalcTextSize("Label").x + bulletSpace,
                                     ImGui::CalcTextSize("Preview").x + bulletSpace,
                                     ImGui::CalcTextSize("Flags").x + bulletSpace}) +
                           10.0f;                                                  // Padding
        float outputWidth = ImGui::CalcTextSize("Return").x + bulletSpace + 10.0f; // Padding

        spdlog::info("Calculated inputWidth: {}, outputWidth: {}", inputWidth, outputWidth);

        // Use previous node width if available, otherwise calculate based on content
        float calculatedWidth = inputWidth + 20.0f + outputWidth;
        float nodeWidth = (prevNodeWidth_ > 0.0f) ? prevNodeWidth_ : calculatedWidth;
        spdlog::info("Using nodeWidth for positioning: {} (calculated: {})", nodeWidth, calculatedWidth);

        float nodePosX = ed::GetNodePosition(id_).x;
        spdlog::info("Node position X: {}", nodePosX);

        // Save starting Y position for side-by-side layout
        float startY = ImGui::GetCursorPosY();

        // Draw inputs group at left
        ImGui::BeginGroup();
        ImGui::Text("Inputs:");

        // Label input pin with visual indicator
        ed::BeginPin(inputPinLabel_, ed::PinKind::Input);
        ImGui::Bullet(); // Visual circle indicator
        ImGui::SameLine();
        ImGui::Text("Label");
        ed::EndPin();

        // Preview input pin with visual indicator
        ed::BeginPin(inputPinPreview_, ed::PinKind::Input);
        ImGui::Bullet(); // Visual circle indicator
        ImGui::SameLine();
        ImGui::Text("Preview");
        ed::EndPin();

        // Flags input pin with visual indicator
        ed::BeginPin(inputPinFlags_, ed::PinKind::Input);
        ImGui::Bullet(); // Visual circle indicator
        ImGui::SameLine();
        ImGui::Text("Flags");
        ed::EndPin();
        ImGui::EndGroup();

        spdlog::info("nodewidth: {}, prevNodeWidth_: {}", nodeWidth, prevNodeWidth_);
        // Position outputs group at right edge of node, same Y
        float outputX = nodeWidth - outputWidth;
        ImGui::SetCursorPos(ImVec2(outputX + nodePosX, startY));
        ImGui::BeginGroup();
        ImGui::Text("Outputs:");

        // Output pin for return value
        ed::BeginPin(outputPinReturn_, ed::PinKind::Output);
        ImGui::Text("Return");
        ImGui::SameLine();
        ImGui::Bullet(); // Visual circle indicator
        ed::EndPin();
        ImGui::EndGroup();

        float actualNodeWidth = ed::GetNodeSize(id_).x;
        spdlog::info("Node width after drawing: {} (was using {})", actualNodeWidth, nodeWidth);

        // Update for next frame
        prevNodeWidth_ = calculatedWidth;

        ed::EndNode();
    }
}