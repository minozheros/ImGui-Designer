
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
          outputPinReturn_(makePinId(id, 4))
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

        // Label input pin
        ed::BeginPin(inputPinLabel_, ed::PinKind::Input);
        ImGui::Text("Label");
        ed::EndPin();

        // Preview input pin
        ed::BeginPin(inputPinPreview_, ed::PinKind::Input);
        ImGui::Text("Preview");
        ed::EndPin();

        // Flags input pin
        ed::BeginPin(inputPinFlags_, ed::PinKind::Input);
        ImGui::Text("Flags");
        ed::EndPin();

        // Parameter controls
        std::array<char, kMaxLabelLen> labelBuf{};
        std::array<char, kMaxPreviewLen> previewBuf{};
        if (params_.label.value.value)
            std::strncpy(labelBuf.data(), params_.label.value.value, kMaxLabelLen - 1);
        if (params_.preview_value.value.value)
            std::strncpy(previewBuf.data(), params_.preview_value.value.value, kMaxPreviewLen - 1);

        ImGui::PushItemWidth(220.0f);
        if (ImGui::InputText("Label", labelBuf.data(), kMaxLabelLen))
        {
            params_.label.value.value = labelBuf.data();
            setInput("label", params_.label.value.value);
        }
        if (ImGui::InputText("Preview", previewBuf.data(), kMaxPreviewLen))
        {
            params_.preview_value.value.value = previewBuf.data();
            setInput("preview_value", params_.preview_value.value.value);
        }
        int flagsInt = static_cast<int>(params_.flags.value.value);
        if (ImGui::InputInt("Flags", &flagsInt))
        {
            params_.flags.value.value = static_cast<ImGuiComboFlags>(flagsInt);
            setInput("flags", params_.flags.value.value);
        }
        ImGui::PopItemWidth();

        // Output pin for return value
        ed::BeginPin(outputPinReturn_, ed::PinKind::Output);
        ImGui::Text("Return");
        ed::EndPin();

        ed::EndNode();
    }
}