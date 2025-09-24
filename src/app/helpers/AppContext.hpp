#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
// External dependencies
#include "core/components/visual_window.hpp"
#include "core/components/toolbar_panel.hpp"
#include <entt/entt.hpp>
#include <imgui.h>
#include <memory>
#include <GLFW/glfw3.h>

// Project headers (project-root relative)
#include "core/helpers/preferences/preferences.hpp"
#include "core/factories/factories.hpp"

struct AppContext
{
public:
    entt::dispatcher dispatcher;
    std::shared_ptr<core::Preferences> preferences;
    // SDL_Renderer *renderer = nullptr;
    GLFWwindow *designerWindow = nullptr;
    ImGuiContext *designerCtx = nullptr;
    std::unique_ptr<core::Factories> factories = nullptr;
    std::unique_ptr<core::VisualWindow> visualWindow;
    std::unique_ptr<core::ToolbarPanel> toolbarPanel;

    AppContext() = default;

    ~AppContext() = default;
};