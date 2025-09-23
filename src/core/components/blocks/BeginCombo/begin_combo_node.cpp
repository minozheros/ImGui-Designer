
#include "begin_combo_node.hpp"
#include <array>
#include <cstring>

namespace
{
    constexpr int kMaxLabelLen = 128;
    constexpr int kMaxPreviewLen = 128;
    ed::PinId makePinId(ed::NodeId nodeId, int offset)
    {
        // NodeId is an opaque handle; use .Get() for unique pins
        return ed::PinId(nodeId.Get() + offset);
    }
}

BeginComboNode::BeginComboNode(ed::NodeId id, const BeginComboParams &params)
    : id_(id), params_(params),
      inputPinId_(makePinId(id, 1)),
      outputPinId_(makePinId(id, 2))
{
    spdlog::info("BeginComboNode constructed, id: {}", id_.Get());
}

BeginComboNode::~BeginComboNode()
{
    spdlog::info("BeginComboNode destroyed, id: {}", id_.Get());
}

void BeginComboNode::draw()
{
    ed::BeginNode(id_);

    ImGui::Text("BeginCombo");
    ed::BeginPin(inputPinId_, ed::PinKind::Input);
    ImGui::Text("In");
    ed::EndPin();

    // Parameter controls
    std::array<char, kMaxLabelLen> labelBuf{};
    std::array<char, kMaxPreviewLen> previewBuf{};
    std::strncpy(labelBuf.data(), params_.label.c_str(), kMaxLabelLen - 1);
    std::strncpy(previewBuf.data(), params_.preview_value.c_str(), kMaxPreviewLen - 1);

    if (ImGui::InputText("Label", labelBuf.data(), kMaxLabelLen))
    {
        params_.label = labelBuf.data();
    }
    if (ImGui::InputText("Preview", previewBuf.data(), kMaxPreviewLen))
    {
        params_.preview_value = previewBuf.data();
    }
    ImGui::InputInt("Flags", reinterpret_cast<int *>(&params_.flags));

    ed::BeginPin(outputPinId_, ed::PinKind::Output);
    ImGui::Text("Out");
    ed::EndPin();

    ed::EndNode();
}
