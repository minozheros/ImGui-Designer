#include "core/components/toolbar_panel.hpp"
#include <spdlog/spdlog.h>
#include "app/helpers/app_context.hpp"

namespace core
{

#include "core/types/maps/node_factory_map.hpp"
#include <algorithm>
    ToolbarPanel::ToolbarPanel(AppContext &appCtx)
        : appContext(appCtx)
    {
        allNodes.reserve(NODE_CLASS_MAP.size());
        for (const auto &pair : NODE_CLASS_MAP)
        {
            allNodes.push_back(pair.first);
        }
        std::sort(allNodes.begin(), allNodes.end());
        spdlog::info("ToolbarPanel constructed with {} nodes (sorted)", allNodes.size());
    }

    void ToolbarPanel::render()
    {
        spdlog::info("ToolbarPanel::render called");
        static float lastWidth = -1.0f;
        ImVec2 avail = ImGui::GetContentRegionAvail();
        if (avail.x < 325.0f)
            avail.x = 325.0f;
        if (avail.x != lastWidth)
        {
            spdlog::info("Toolbar width changed: {} px", avail.x);
            lastWidth = avail.x;
        }
        float focusAreaWidth = avail.x - 2.0f;
        if (focusAreaWidth < 325.0f)
            focusAreaWidth = 325.0f;
        // Render search bar at the top (always visible)
        ImGui::PushID("ToolbarSearchBox");
        float inputWidth = ImGui::GetContentRegionAvail().x;
        const char *label = "Search nodes";
        ImVec2 labelSize = ImGui::CalcTextSize(label);
        float minInputWidth = 80.0f;
        float spacing = ImGui::GetStyle().ItemSpacing.x;
        float totalNeeded = labelSize.x + spacing + minInputWidth;
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
        // Auto-focus logic remains unchanged
        ImVec2 mouse = ImGui::GetIO().MousePos;
        ImRect childRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + focusAreaWidth, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y));
        static bool searchAutoFocused = false;
        static bool mouseWasInside = false;
        auto &io = ImGui::GetIO();
        bool inside = childRect.Contains(mouse);
        bool canAutofocus = true;
        if (inside && canAutofocus)
        {
            if (!mouseWasInside && !io.MouseDown[0] && !searchAutoFocused)
            {
                ImGui::SetKeyboardFocusHere(-1);
                searchAutoFocused = true;
            }
            if (ImGui::IsMouseReleased(0))
            {
                if (!searchAutoFocused)
                {
                    ImGui::SetKeyboardFocusHere(-1);
                    searchAutoFocused = true;
                }
            }
        }
        else if (!inside)
        {
            searchAutoFocused = false;
        }
        mouseWasInside = inside;
        ImGui::PopID();

        // Calculate height for scrollable node list (remaining space)
        float listHeight = ImGui::GetContentRegionAvail().y;
        ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarSize, 20.0f); // Set vertical scrollbar width to 20px
        ImGui::BeginChild("ToolbarNodeList", ImVec2(focusAreaWidth, listHeight), true, ImGuiWindowFlags_HorizontalScrollbar);
        std::string searchLower = toLower(nodeSearch);
        float buttonWidth = ImGui::GetContentRegionAvail().x;
        // Group nodes by first word
        std::map<std::string, std::vector<std::string>> groupedNodes;
        for (const auto &nodeName : allNodes)
        {
            std::string firstWord = nodeName;
            size_t spacePos = nodeName.find(' ');
            if (spacePos != std::string::npos)
            {
                firstWord = nodeName.substr(0, spacePos);
            }
            else
            {
                // If no space, try to split at uppercase letter (CamelCase)
                size_t splitPos = 1;
                while (splitPos < nodeName.size() && !isupper(nodeName[splitPos]))
                    ++splitPos;
                if (splitPos > 1 && splitPos < nodeName.size())
                    firstWord = nodeName.substr(0, splitPos);
            }
            groupedNodes[firstWord].push_back(nodeName);
        }

        for (const auto &group : groupedNodes)
        {
            ImGui::Separator();
            ImGui::PushID((group.first + "_header").c_str());
            if (ImGui::CollapsingHeader(group.first.c_str(), ImGuiTreeNodeFlags_DefaultOpen))
            {
                for (const auto &nodeName : group.second)
                {
                    ImGui::PushID((nodeName + "_node").c_str());
                    std::string nodeLower = toLower(nodeName);
                    if (searchLower.empty() || nodeLower.find(searchLower) != std::string::npos)
                    {
                        bool clicked = ImGui::Button(nodeName.c_str(), ImVec2(buttonWidth, 0));
                        // ...existing button logic...
                        bool hovered = ImGui::IsItemHovered();
                        bool active = ImGui::IsItemActive();
                        bool itemClicked = ImGui::IsItemClicked(0);
                        auto &io = ImGui::GetIO();
                        bool mouseDown = io.MouseDown[0];
                        bool wantCapture = io.WantCaptureMouse;
                        spdlog::info("ToolbarPanel: Button '{}' state -> clicked={}, hovered={}, active={}, itemClicked={}, mouseDown={}, wantCapture={}", nodeName, clicked, hovered, active, itemClicked, mouseDown, wantCapture);
                        ImVec2 itemMin = ImGui::GetItemRectMin();
                        ImVec2 itemMax = ImGui::GetItemRectMax();
                        ImGuiID itemId = ImGui::GetItemID();
                        ImGuiID hoveredId = ImGui::GetHoveredID();
                        ImGuiWindow *curWin = ImGui::GetCurrentWindow();
                        const char *winName = curWin ? curWin->Name : "(null)";
                        bool winHovered = ImGui::IsWindowHovered();
                        bool winFocused = ImGui::IsWindowFocused();
                        spdlog::info("ToolbarPanel: ItemRect=({},{})->({},{}) ItemID={} HoveredID={} Window='{}' winHovered={} winFocused={} MousePos=({:.1f},{:.1f})",
                                     itemMin.x, itemMin.y, itemMax.x, itemMax.y, (unsigned)itemId, (unsigned)hoveredId, winName, winHovered, winFocused, io.MousePos.x, io.MousePos.y);
                        if (clicked)
                        {
                            spdlog::info("ToolbarPanel: Button '{}' clicked", nodeName);
                            VisualWindow *gVisualWindow = appContext.visualWindow.get();
                            spdlog::info("ToolbarPanel: VisualWindow pointer is {}", (gVisualWindow ? "valid" : "null"));
                            if (gVisualWindow)
                            {
                                auto block = appContext.factories->nodeFactory.get()->createBlockByName(nodeName);
                                if (block)
                                {
                                    const auto &blockRef = *block;
                                    spdlog::info("ToolbarPanel: Created block of type '{}'", typeid(blockRef).name());
                                    gVisualWindow->addBlock(std::move(block));
                                }
                                else
                                {
                                    spdlog::warn("ToolbarPanel: Failed to create block for node '{}'", nodeName);
                                }
                            }
                            else
                            {
                                spdlog::warn("ToolbarPanel: Cannot add block, VisualWindow is null");
                            }
                        }
                        else
                        {
                            auto &io2 = ImGui::GetIO();
                            spdlog::info("ToolbarPanel: Click not registered -> MousePos=({:.1f},{:.1f}), MouseDown[0]={}, MouseDownDuration[0]={:.3f}, IsMouseClicked(0)={}, ActiveID={}, HoveredID={}", io2.MousePos.x, io2.MousePos.y, io2.MouseDown[0], io2.MouseDownDuration[0], ImGui::IsMouseClicked(0), ImGui::GetActiveID(), ImGui::GetHoveredID());
                        }
                    }
                    ImGui::PopID();
                }
            }
            ImGui::PopID();
        }
        ImGui::EndChild();
        ImGui::PopStyleVar();
    }

    std::string ToolbarPanel::toLower(const std::string &s)
    {
        std::string out = s;
        for (char &c : out)
            c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
        return out;
    }

} // namespace core
