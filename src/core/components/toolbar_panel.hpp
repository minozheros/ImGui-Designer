#include <spdlog/spdlog.h>
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <string>
#include <vector>

namespace core
{
    class ToolbarPanel
    {
        std::string nodeSearch;
        char searchBuffer[128] = "";
        std::vector<std::string> allNodes;

    public:
        ToolbarPanel()
            : allNodes{"Add", "Subtract", "Multiply", "Divide", "Sin", "Cos", "Log", "Exp", "Clamp", "Lerp", "UI_Button", "UI_Slider", "Input_Int", "Output_Float"} {}

        // Helper: lowercase a string
        static std::string toLower(const std::string &s)
        {
            std::string out = s;
            for (char &c : out)
                c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
            return out;
        }

        void render()
        {
            // Track and log toolbar width changes
            static float lastWidth = -1.0f;
            ImVec2 avail = ImGui::GetContentRegionAvail();
            // Enforce minimum width of 200px
            if (avail.x < 200.0f)
                avail.x = 200.0f;
            if (avail.x != lastWidth)
            {
                spdlog::info("Toolbar width changed: {} px", avail.x);
                lastWidth = avail.x;
            }
            float focusAreaWidth = avail.x - 2.0f;
            if (focusAreaWidth < 200.0f)
                focusAreaWidth = 200.0f;
            ImGui::BeginChild("ToolbarFocusArea", ImVec2(focusAreaWidth, 0), false, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground);

            // Draw the search box
            ImGui::PushID("ToolbarSearchBox");
            float inputWidth = ImGui::GetContentRegionAvail().x;
            const char *label = "Search nodes";
            ImVec2 labelSize = ImGui::CalcTextSize(label);
            float minInputWidth = 80.0f;
            float spacing = ImGui::GetStyle().ItemSpacing.x;
            float totalNeeded = labelSize.x + spacing + minInputWidth;
            // If not enough space, stack label and input vertically
            if (inputWidth < totalNeeded)
            {
                ImGui::TextUnformatted(label);
                ImGui::SetNextItemWidth(inputWidth);
                if (ImGui::InputText("##search_nodes", searchBuffer, IM_ARRAYSIZE(searchBuffer)))
                {
                    nodeSearch = searchBuffer;
                }
            }
            else
            {
                ImGui::TextUnformatted(label);
                ImGui::SameLine();
                ImGui::SetNextItemWidth(inputWidth - labelSize.x - spacing);
                if (ImGui::InputText("##search_nodes", searchBuffer, IM_ARRAYSIZE(searchBuffer)))
                {
                    nodeSearch = searchBuffer;
                }
            }
            // Only focus if mouse is >10px from the right edge (i.e., inside the child window)
            ImVec2 mouse = ImGui::GetIO().MousePos;
            ImRect childRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + focusAreaWidth, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y));
            if (childRect.Contains(mouse))
            {
                ImGui::SetKeyboardFocusHere(-1);
            }
            ImGui::PopID();

            // Case-insensitive search and node buttons
            std::string searchLower = toLower(nodeSearch);
            float buttonWidth = ImGui::GetContentRegionAvail().x;
            for (const auto &nodeName : allNodes)
            {
                std::string nodeLower = toLower(nodeName);
                if (searchLower.empty() || nodeLower.find(searchLower) != std::string::npos)
                {
                    if (ImGui::Button(nodeName.c_str(), ImVec2(buttonWidth, 0)))
                    {
                        // TODO: Handle node selection/creation
                    }
                }
            }
            ImGui::EndChild();
        }
    };
} // namespace core
