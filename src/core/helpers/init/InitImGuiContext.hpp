// External dependencies
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <spdlog/spdlog.h>

// Project headers

namespace core
{
    int InitImGuiContext(ImGuiContext *&ctx, GLFWwindow *&window)
    {
        ctx = ImGui::CreateContext();
        ImGui::SetCurrentContext(ctx);
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.IniFilename = NULL;
        ImGui_ImplGlfw_InitForOpenGL(window, false); // Don't install callbacks, we'll handle them manually
        ImGui_ImplOpenGL3_Init("#version 330");
        // Load fonts for this context
        io.Fonts->AddFontFromFileTTF("fonts/arial.ttf", 16.0f);
        io.Fonts->AddFontFromFileTTF("fonts/Quartz.ttf", 16.0f);
        return 0;
    }
}