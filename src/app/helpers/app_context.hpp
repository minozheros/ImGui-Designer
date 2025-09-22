#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
// External dependencies
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
    AppContext() = default;
    ~AppContext() = default;
};