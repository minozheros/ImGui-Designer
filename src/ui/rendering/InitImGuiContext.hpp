// External dependencies
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <spdlog/spdlog.h>
#include <SDL3/SDL.h>

// Project headers

int InitImGuiContext(ImGuiContext *&ctx, SDL_Window *window)
{
    ctx = ImGui::CreateContext();
    ImGui::SetCurrentContext(ctx);
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = NULL;
    ImGui_ImplSDL3_InitForOpenGL(window, nullptr);
    ImGui_ImplOpenGL3_Init("#version 330");
    // Load fonts for this context
    io.Fonts->AddFontFromFileTTF("fonts/arial.ttf", 16.0f);
    io.Fonts->AddFontFromFileTTF("fonts/Quartz.ttf", 16.0f);
    return 0;
}