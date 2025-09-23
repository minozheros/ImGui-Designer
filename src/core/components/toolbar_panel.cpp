#include "core/components/toolbar_panel.hpp"
#include <spdlog/spdlog.h>
#include "app/helpers/app_context.hpp"

namespace core
{

    ToolbarPanel::ToolbarPanel(AppContext &appCtx)
        : allNodes{"BeginCombo"}, appContext(appCtx)
    {
        spdlog::info("ToolbarPanel constructed");
    }

    void ToolbarPanel::render()
    {
        spdlog::info("ToolbarPanel::render called");
        static float lastWidth = -1.0f;
        ImVec2 avail = ImGui::GetContentRegionAvail();
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
        // Auto-focus the search input only once when the mouse enters the toolbar area.
        // This avoids forcing focus every frame (which can interfere with mouse clicks).
        ImVec2 mouse = ImGui::GetIO().MousePos;
        ImRect childRect(ImGui::GetWindowPos(), ImVec2(ImGui::GetWindowPos().x + focusAreaWidth, ImGui::GetWindowPos().y + ImGui::GetWindowSize().y));
        // Focus the search box on mouse-release inside the toolbar, but only if the release wasn't over another item.
        static bool searchAutoFocused = false;
        auto &io = ImGui::GetIO();
        if (childRect.Contains(mouse))
        {
            // Only react to the release event (avoids stealing clicks on buttons)
            if (ImGui::IsMouseReleased(0) && ImGui::GetHoveredID() == 0)
            {
                if (!searchAutoFocused)
                {
                    ImGui::SetKeyboardFocusHere(-1);
                    searchAutoFocused = true;
                }
            }
        }
        else
        {
            // Reset so next valid release will refocus once
            searchAutoFocused = false;
        }
        ImGui::PopID();

        // If the toolbar window isn't hovered, clear any active ImGui item to avoid blocking mouse input
        bool toolbarHovered = ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem);
        ImGuiID activeIdBefore = ImGui::GetActiveID();
        if (!toolbarHovered && activeIdBefore != 0)
        {
            spdlog::info("ToolbarPanel: clearing active ImGui ID {} because toolbar not hovered", (unsigned)activeIdBefore);
            ImGui::ClearActiveID();
        }

        std::string searchLower = toLower(nodeSearch);
        float buttonWidth = ImGui::GetContentRegionAvail().x;
        for (const auto &nodeName : allNodes)
        {
            spdlog::info("ToolbarPanel: Checking node '{}'", nodeName);
            std::string nodeLower = toLower(nodeName);
            if (searchLower.empty() || nodeLower.find(searchLower) != std::string::npos)
            {
                // Render button and capture interaction state
                // Create the button and capture the return value explicitly
                bool clicked = ImGui::Button(nodeName.c_str(), ImVec2(buttonWidth, 0));

                // Immediately after the button, query ImGui item/input state
                bool hovered = ImGui::IsItemHovered();
                bool active = ImGui::IsItemActive();
                bool itemClicked = ImGui::IsItemClicked(0);
                auto &io = ImGui::GetIO();
                bool mouseDown = io.MouseDown[0];
                bool wantCapture = io.WantCaptureMouse;

                spdlog::info("ToolbarPanel: Button '{}' state -> clicked={}, hovered={}, active={}, itemClicked={}, mouseDown={}, wantCapture={}", nodeName, clicked, hovered, active, itemClicked, mouseDown, wantCapture);

                // Extra diagnostics: item rects, item id, hovered id, window info
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
                    if (gVisualWindow && nodeName == "BeginCombo")
                    {
                        static int nextId = 1;
                        BeginComboParams params;
                        params.label = "Label";
                        params.preview_value = "Preview";
                        params.flags = 0;
                        auto node = std::make_unique<BeginComboNode>(ed::NodeId(nextId++), params);
                        spdlog::info("ToolbarPanel: Adding BeginComboNode to VisualWindow");
                        gVisualWindow->addBlock(std::move(node));
                    }
                }
                else
                {
                    auto &io2 = ImGui::GetIO();
                    spdlog::info("ToolbarPanel: Click not registered -> MousePos=({:.1f},{:.1f}), MouseDown[0]={}, MouseDownDuration[0]={:.3f}, IsMouseClicked(0)={}, ActiveID={}, HoveredID={}", io2.MousePos.x, io2.MousePos.y, io2.MouseDown[0], io2.MouseDownDuration[0], ImGui::IsMouseClicked(0), ImGui::GetActiveID(), ImGui::GetHoveredID());
                }
            }
        }
        ImGui::EndChild();
    }

    std::string ToolbarPanel::toLower(const std::string &s)
    {
        std::string out = s;
        for (char &c : out)
            c = static_cast<char>(::tolower(static_cast<unsigned char>(c)));
        return out;
    }

} // namespace core
