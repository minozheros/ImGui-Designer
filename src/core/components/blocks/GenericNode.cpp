#include "GenericNode.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <spdlog/spdlog.h>
#include <algorithm>

namespace core
{
    void GenericNode::render()
    {
        ImGui::BeginGroup();
        float nodeWidth = 180.0f;
        float inputWidth = 0.0f;
        float outputWidth = 0.0f;
        float pinHeight = 20.0f;
        int inputCount = 0, outputCount = 0;
        for (auto *param : params_)
        {
            float labelWidth = ImGui::CalcTextSize(param->getName().c_str()).x;
            if (param->getType() == ParameterType::INPUT)
            {
                inputWidth = std::max(inputWidth, labelWidth);
                inputCount++;
            }
            else if (param->getType() == ParameterType::RETURN)
            {
                outputWidth = std::max(outputWidth, labelWidth);
                outputCount++;
            }
        }
        nodeWidth = std::max(nodeWidth, inputWidth + outputWidth + 40.0f);
        float titleWidth = ImGui::CalcTextSize(title_.c_str()).x;
        float titleX = (nodeWidth - titleWidth) * 0.5f;
        ImGui::SetCursorPosX(titleX);
        ImGui::Text("%s", title_.c_str());
        float y = ImGui::GetCursorPosY() + 10.0f;
        // Inputs
        for (auto *param : params_)
        {
            if (param->getType() == ParameterType::INPUT)
            {
                ImGui::SetCursorPos(ImVec2(10.0f, y));
                ImGui::Text("%s", param->getName().c_str());
                y += pinHeight;
            }
        }
        // Outputs
        y = ImGui::GetCursorPosY() + 10.0f;
        for (auto *param : params_)
        {
            if (param->getType() == ParameterType::RETURN)
            {
                ImGui::SetCursorPos(ImVec2(nodeWidth - outputWidth - 20.0f, y));
                ImGui::Text("%s", param->getName().c_str());
                y += pinHeight;
            }
        }
        prevNodeWidth_ = nodeWidth;
        spdlog::debug("GenericNode: nodeWidth={}, inputWidth={}, outputWidth={}", nodeWidth, inputWidth, outputWidth);
        ImGui::EndGroup();
    }
}
