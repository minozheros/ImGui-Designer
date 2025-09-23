#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
// External dependencies
#include "core/components/visual_window.hpp"
#include <entt/entt.hpp>
#include <imgui.h>
#include <memory>
#include <GLFW/glfw3.h>

// Project headers (project-root relative)
#include "core/helpers/preferences/preferences.hpp"
#include "core/factories/factories.hpp"

struct AppContext
{
    entt::dispatcher dispatcher;
    std::shared_ptr<core::Preferences> preferences;
    // SDL_Renderer *renderer = nullptr;
    GLFWwindow *designerWindow = nullptr;
    GLFWwindow *previewWindow = nullptr;
    ImGuiContext *designerCtx = nullptr;
    ImGuiContext *previewCtx = nullptr;
    std::unique_ptr<core::Factories> factories = nullptr;
    std::unique_ptr<VisualWindow> visualWindow;

    AppContext()
        : visualWindow(std::make_unique<VisualWindow>()) {}
    ~AppContext() = default;

    VisualWindow *getVisualWindow() { return visualWindow.get(); }
};