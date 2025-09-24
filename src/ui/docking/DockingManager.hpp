#pragma once
#include <imgui.h>
#include <imgui_internal.h>
#include <spdlog/spdlog.h>

class DockingManager
{
public:
    DockingManager();
    ~DockingManager() = default;

    /**
     * Sets up the main dockspace layout for the designer window.
     * This includes creating the dockspace, splitting it into regions,
     * and assigning windows to dock positions.
     *
     * Call this after ImGui::NewFrame() and before rendering individual windows.
     */
    void setupDockspace();

    /**
     * Applies workarounds for toolbar positioning when the dock layout
     * causes the toolbar to be too narrow.
     *
     * Call this before rendering the Toolbar window.
     */
    void applyToolbarWorkarounds();

private:
    // Static dock IDs for persistent layout
    static ImGuiID dock_id_left;
};