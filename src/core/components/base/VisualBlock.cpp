#include "core/components/base/visual_block.hpp"
#include <algorithm>
#include <imgui.h>

ImVec2 VisualBlock::getPreferredSize(const char *name, const char *value, int numInputs, int numOutputs) const
{
    float width = 0.0f;
    float height = 0.0f;
    if (name)
    {
        ImVec2 nameSize = ImGui::CalcTextSize(name);
        if (nameSize.x + 24.0f > width)
            width = nameSize.x + 24.0f;
        height += nameSize.y;
    }
    if (value)
    {
        ImVec2 valueSize = ImGui::CalcTextSize(value);
        if (valueSize.x + 24.0f > width)
            width = valueSize.x + 24.0f;
        height += valueSize.y;
    }
    int maxLabels = std::max(numInputs, numOutputs);
    height += maxLabels * 20.0f;
    height += 5.0f;
    if (width < 60.0f)
        width = 60.0f;
    return ImVec2(width, height);
}

void VisualBlock::setInput(const std::string &name, std::any value)
{
    inputs_[name] = value;
}

std::any VisualBlock::getOutput(const std::string &name) const
{
    auto it = outputs_.find(name);
    if (it != outputs_.end())
        return it->second;
    return {};
}

void VisualBlock::setOutput(const std::string &name, std::any value)
{
    outputs_[name] = value;
}

const std::unordered_map<std::string, std::any> &VisualBlock::getInputs() const
{
    return inputs_;
}

const std::unordered_map<std::string, std::any> &VisualBlock::getOutputs() const
{
    return outputs_;
}
