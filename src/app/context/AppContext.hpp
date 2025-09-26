#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
// External dependencies
#include "ui/components/VisualWindow.hpp"
#include "ui/components/ToolbarPanel.hpp"
#include "ui/panels/PackManagerPanel.hpp"
#include "ui/panels/PackViewerPanel.hpp"
#include "ui/panels/FirstRunModal.hpp"
#include "app/state/AppStateStore.hpp"
#include "app/state/LayoutStore.hpp"
#include "app/state/ProjectService.hpp"
#include "ui/components/MainMenuBar.hpp"
#include <entt/entt.hpp>
#include <imgui.h>
#include <memory>
#include <SDL3/SDL.h>

// Project headers (project-root relative)
#include "core/helpers/preferences/Preferences.hpp"
#include "node/factories/Factories.hpp"
#include "ui/docking/DockingManager.hpp"

struct AppContext
{
public:
    entt::dispatcher dispatcher;
    std::shared_ptr<Preferences> preferences;
    SDL_Window *designerWindow = nullptr;
    SDL_GLContext glContext = nullptr;
    ImGuiContext *designerCtx = nullptr;
    std::unique_ptr<Factories> factories = nullptr;
    std::unique_ptr<VisualWindow> visualWindow;
    std::unique_ptr<ToolbarPanel> toolbarPanel;
    std::unique_ptr<DockingManager> dockingManager;
    std::unique_ptr<ui::panels::PackManagerPanel> packManagerPanel;
    std::unique_ptr<ui::panels::PackViewerPanel> packViewerPanel;
    std::unique_ptr<ui::panels::FirstRunModal> firstRunModal;
    app::state::AppStateStore stateStore;
    app::state::LayoutStore layoutStore;
    app::state::ProjectService projectService; // scaffold for new/open/save actions
    std::unique_ptr<ui::components::MainMenuBar> mainMenuBar;

    AppContext() = default;

    ~AppContext() = default;
};