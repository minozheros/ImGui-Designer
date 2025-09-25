#include "DockingManager.hpp"

ImGuiID DockingManager::dock_id_left = 0;

DockingManager::DockingManager()
{
    // Initialize static members if needed
}

void DockingManager::setupDockspace()
{
    // Fill the main viewport with the dockspace host window, removing all padding and constraints
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGuiWindowFlags host_window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSizeConstraints(viewport->Size, viewport->Size);
    ImGui::Begin("MainDockSpace", nullptr, host_window_flags);
    ImGui::PopStyleVar(3);

    ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
    if (ImGui::DockBuilderGetNode(dockspace_id) == nullptr)
    {
        ImGui::DockBuilderRemoveNode(dockspace_id); // clear any previous layout
        ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);

        ImVec2 dockspace_size = viewport ? viewport->Size : ImVec2(1280, 720);
        spdlog::info("Viewport size: x={}, y={}", dockspace_size.x, dockspace_size.y);
        if (dockspace_size.x <= 0.0f || dockspace_size.y <= 0.0f)
        {
            spdlog::warn("Dockspace size invalid (x={}, y={}), using fallback.", dockspace_size.x, dockspace_size.y);
            dockspace_size = ImVec2(1280, 720); // fallback to default size
        }
        spdlog::info("DockBuilderSetNodeSize using: x={}, y={}", dockspace_size.x, dockspace_size.y);
        ImGui::DockBuilderSetNodeSize(dockspace_id, dockspace_size);

        // Split: left (toolbar), main, bottom
        ImGuiID dock_main_id = dockspace_id;
        dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.15f, nullptr, &dock_main_id);
        ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, nullptr, &dock_main_id);

        // Dock windows
        // Toolbar area (left): make Pack Manager and Pack Viewer tabs next to Toolbar
        ImGui::DockBuilderDockWindow("Toolbar", dock_id_left);
        ImGui::DockBuilderDockWindow("Pack Manager", dock_id_left);
        ImGui::DockBuilderDockWindow("Pack Viewer", dock_id_left);

        // Bottom bar and main designer canvas in the remaining regions
        ImGui::DockBuilderDockWindow("BottomBar", dock_id_bottom);
        ImGui::DockBuilderDockWindow("Designer", dock_main_id);

        ImGui::DockBuilderFinish(dockspace_id);
    }
    else
    {
        // If a layout already exists (from ini), ensure Pack Manager and Pack Viewer are docked
        // as tabs with the Toolbar by locating the Toolbar's dock node.
        ImGuiWindow *toolbarWindow = ImGui::FindWindowByName("Toolbar");
        if (toolbarWindow && toolbarWindow->DockNode)
        {
            ImGuiID toolbarDockId = toolbarWindow->DockNode->ID;
            ImGui::DockBuilderDockWindow("Pack Manager", toolbarDockId);
            ImGui::DockBuilderDockWindow("Pack Viewer", toolbarDockId);
        }
    }

    // ImGui internal workaround: enforce minimum dock node width for toolbar
    if (dock_id_left != 0)
    {
        ImGuiDockNode *node = ImGui::DockBuilderGetNode(dock_id_left);
        if (node && node->Size.x < 375.0f)
        {
            node->Size.x = 375.0f;
            node->SizeRef.x = 375.0f;
        }
    }

    ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::End();
}

void DockingManager::applyToolbarWorkarounds()
{
    // Workaround: If the toolbar is too narrow, move and resize it to prevent clipping
    ImVec2 toolbarPos, toolbarSize;
    bool hasToolbarRect = false;
    if (ImGui::FindWindowByName("Toolbar"))
    {
        ImGuiWindow *win = ImGui::FindWindowByName("Toolbar");
        toolbarPos = win->Pos;
        toolbarSize = win->Size;
        hasToolbarRect = true;
    }
    if (hasToolbarRect && toolbarSize.x < 375.0f)
    {
        ImGui::SetNextWindowPos(ImVec2(toolbarPos.x + (375.0f - toolbarSize.x) + 10.0f, toolbarPos.y));
        ImGui::SetNextWindowSize(ImVec2(375.0f, toolbarSize.y));
    }
    else
    {
        ImGui::SetNextWindowSizeConstraints(ImVec2(375.0f, 0.0f), ImVec2(FLT_MAX, FLT_MAX));
    }
}