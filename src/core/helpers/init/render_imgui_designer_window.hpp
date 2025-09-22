#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>
#include "app/helpers/app_context.hpp"
namespace core
{
    int RenderDesignerWindow(AppContext &ctx, ImGuiContext *imguiCtx, GLFWwindow *window)
    {
        glfwMakeContextCurrent(window);
        ImGui::SetCurrentContext(imguiCtx);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        spdlog::debug("Rendering Designer screen");

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
            ImGuiID dock_id_left = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Left, 0.15f, nullptr, &dock_main_id);
            ImGuiID dock_id_bottom = ImGui::DockBuilderSplitNode(dock_main_id, ImGuiDir_Down, 0.20f, nullptr, &dock_main_id);

            // Dock windows
            ImGui::DockBuilderDockWindow("Toolbar", dock_id_left);
            ImGui::DockBuilderDockWindow("BottomBar", dock_id_bottom);
            ImGui::DockBuilderDockWindow("MainArea", dock_main_id);

            ImGui::DockBuilderFinish(dockspace_id);
        }

        ImGui::DockSpace(dockspace_id, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::End();

        // Then, in your UI code, create windows with matching names:
        ImGui::Begin("Toolbar");
        // ... toolbar content ...
        ImGui::End();

        ImGui::Begin("BottomBar");
        // ... bottom bar content ...
        ImGui::End();

        ImGui::Begin("MainArea");
        // ... main workspace content ...
        ImGui::End();

        ImGui::Render();
        ImGui::EndFrame();

        int display_w = 0, display_h = 0;
        if (window)
        {

            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        return 0;
    }
}