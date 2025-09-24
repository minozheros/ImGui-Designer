#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <spdlog/spdlog.h>
#include <SDL3/SDL.h>
#include "app/context/AppContext.hpp"
#include "ui/components/ToolbarPanel.hpp"
#include "X11MouseFix.hpp"
#include "ui/docking/DockingManager.hpp"

int RenderDesignerWindow(AppContext &ctx, ImGuiContext *imguiCtx, SDL_Window *window)
{
    // Ensure global pointer is set for toolbar node addition
    VisualWindow *gVisualWindow = ctx.visualWindow.get();

    // Make OpenGL context current (SDL handles this automatically in most cases)
    SDL_GL_MakeCurrent(window, ctx.glContext);

    // Log SDL input state before beginning ImGui frame
    if (window)
    {
        bool win_focused = SDL_GetWindowFlags(window) & SDL_WINDOW_INPUT_FOCUS;
        bool win_hovered = SDL_GetWindowFlags(window) & SDL_WINDOW_MOUSE_FOCUS;
        float cx = 0.0f, cy = 0.0f;
        SDL_GetMouseState(&cx, &cy);
        spdlog::info("SDL state: focused={}, hovered={}, cursorPos=({}, {})", win_focused, win_hovered, cx, cy);
    }

    ImGui::SetCurrentContext(imguiCtx);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();

    // SDL3 handles multi-monitor coordinate issues automatically

    // After ImGui new frame, log ImGui IO state for comparison with SDL
    ImGuiIO &io = ImGui::GetIO();
    spdlog::info("ImGui IO: MousePos=({}, {}), MouseDown[0]={}, MouseDownDuration[0]={}, WantCaptureMouse={}", io.MousePos.x, io.MousePos.y, io.MouseDown[0], io.MouseDownDuration[0], io.WantCaptureMouse);
    if (window)
    {
        int wx = 0, wy = 0, ww = 0, wh = 0;
        SDL_GetWindowPosition(window, &wx, &wy);
        SDL_GetWindowSize(window, &ww, &wh);
        spdlog::info("SDL window pos/size: pos=({}, {}), size=({}, {})", wx, wy, ww, wh);
        float cx = 0.0f, cy = 0.0f;
        SDL_GetMouseState(&cx, &cy);
        spdlog::info("Cursor global pos=({}, {}), local pos relative to window=({}, {})", cx, cy, cx - wx, cy - wy);
    }

    spdlog::debug("Rendering Designer screen");
    spdlog::debug("RenderDesignerWindow: incoming imguiCtx={}, ImGui::GetCurrentContext()={}", (void *)imguiCtx, (void *)ImGui::GetCurrentContext());
    spdlog::info("RenderDesignerWindow: imguiCtx pointer={}, ImGui::GetCurrentContext()={}", (void *)imguiCtx, (void *)ImGui::GetCurrentContext());

    // Setup the dockspace layout
    if (ctx.dockingManager)
    {
        ctx.dockingManager->setupDockspace();
        // Then, in your UI code, create windows with matching names:
        // Use persistent ToolbarPanel from AppContext
        ctx.dockingManager->applyToolbarWorkarounds();
    }

    ImGui::Begin("Toolbar");
    if (ctx.toolbarPanel)
    {
        // ctx.toolbarPanel->render();
    }
    ImGui::End();

    ImGui::Begin("BottomBar");
    // ... bottom bar content ...
    ImGui::End();

    ImGui::Begin("MainArea");
    if (ctx.visualWindow)
    {
        // ctx.visualWindow->render();
    }
    ImGui::End();

    ImGui::Render();
    ImGui::EndFrame();

    int display_w = 0, display_h = 0;
    if (window)
    {
        SDL_GetWindowSizeInPixels(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    SDL_GL_SwapWindow(window);

    return 0;
}