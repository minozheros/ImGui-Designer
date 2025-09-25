#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl3.h>
#include <spdlog/spdlog.h>
#include <SDL3/SDL.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <string>
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
        // Demoted from info to debug (per-frame loop)
        spdlog::debug("SDL state: focused={}, hovered={}, cursorPos=({}, {})", win_focused, win_hovered, cx, cy);
    }

    ImGui::SetCurrentContext(imguiCtx);
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL3_NewFrame();

    ImGui::NewFrame();

    // Top menu bar
    if (ctx.mainMenuBar)
    {
        ctx.mainMenuBar->render();
    }

    // SDL3 handles multi-monitor coordinate issues automatically

    // After ImGui new frame, log ImGui IO state for comparison with SDL
    ImGuiIO &io = ImGui::GetIO();
    // Demoted from info to debug (per-frame IO state)
    spdlog::debug("ImGui IO: MousePos=({}, {}), MouseDown[0]={}, MouseDownDuration[0]={}, WantCaptureMouse={}", io.MousePos.x, io.MousePos.y, io.MouseDown[0], io.MouseDownDuration[0], io.WantCaptureMouse);
    if (window)
    {
        int wx = 0, wy = 0, ww = 0, wh = 0;
        SDL_GetWindowPosition(window, &wx, &wy);
        SDL_GetWindowSize(window, &ww, &wh);
        // Demoted from info to debug (per-frame window metrics)
        spdlog::debug("SDL window pos/size: pos=({}, {}), size=({}, {})", wx, wy, ww, wh);
        float cx = 0.0f, cy = 0.0f;
        SDL_GetMouseState(&cx, &cy);
        // Demoted from info to debug (per-frame cursor metrics)
        spdlog::debug("Cursor global pos=({}, {}), local pos relative to window=({}, {})", cx, cy, cx - wx, cy - wy);
    }

    spdlog::debug("Rendering Designer screen");
    spdlog::debug("RenderDesignerWindow: incoming imguiCtx={}, ImGui::GetCurrentContext()={}", (void *)imguiCtx, (void *)ImGui::GetCurrentContext());
    // Demoted from info to debug (per-frame context pointer)
    spdlog::debug("RenderDesignerWindow: imguiCtx pointer={}, ImGui::GetCurrentContext()={}", (void *)imguiCtx, (void *)ImGui::GetCurrentContext());

    // Setup the dockspace layout
    if (ctx.dockingManager)
    {
        ctx.dockingManager->setupDockspace();
        // Then, in your UI code, create windows with matching names:
        // Use persistent ToolbarPanel from AppContext
        ctx.dockingManager->applyToolbarWorkarounds();
    }

    // Decide initial focused tab in the left dock (Toolbar vs Pack Manager vs Pack Viewer)
    // Order of precedence (applied once):
    // 1) User's last saved choice from app_state.json
    // 2) If none saved and no ImGui ini: Toolbar by default, unless no packs installed -> Pack Manager
    static bool didSetInitialFocus = false;
    static bool noPacksInstalled = false;
    static bool hasImGuiIni = false;
    static bool iniChecked = false;
    static bool loadedSavedLeftTab = false;
    static std::string savedLeftTab;
    if (!iniChecked)
    {
        const ImGuiIO &io2 = ImGui::GetIO();
        if (io2.IniFilename && *io2.IniFilename)
        {
            hasImGuiIni = std::filesystem::exists(std::filesystem::path(io2.IniFilename));
        }
        else
        {
            hasImGuiIni = false;
        }
        iniChecked = true;
    }
    if (!didSetInitialFocus)
    {
        // Determine if packs are installed by checking registry/packs.lock.json for entries
        try
        {
            std::ifstream lf("registry/packs.lock.json");
            if (lf.is_open())
            {
                nlohmann::json j;
                lf >> j;
                if (j.contains("entries") && j["entries"].is_array() && !j["entries"].empty())
                    noPacksInstalled = false;
                else
                    noPacksInstalled = true;
            }
            else
            {
                noPacksInstalled = true;
            }
        }
        catch (...)
        {
            noPacksInstalled = true;
        }
        // Load project-saved last-left-tab once
        if (!loadedSavedLeftTab)
        {
            auto t = ctx.stateStore.loadLastLeftTab();
            if (t.has_value())
                savedLeftTab = *t;
            loadedSavedLeftTab = true;
        }
    }

    // Resolve which window should receive initial focus (applied once before its Begin)
    bool focusToolbar = false;
    bool focusPackManager = false;
    bool focusPackViewer = false;
    if (!didSetInitialFocus)
    {
        if (!savedLeftTab.empty())
        {
            if (savedLeftTab == "Toolbar")
                focusToolbar = true;
            else if (savedLeftTab == "Pack Manager")
                focusPackManager = true;
            else if (savedLeftTab == "Pack Viewer")
                focusPackViewer = true;
        }
        else if (!hasImGuiIni)
        {
            // Use default heuristic only when no saved preference and no preset ini
            if (noPacksInstalled)
                focusPackManager = true;
            else
                focusToolbar = true;
        }
    }

    if (focusToolbar)
    {
        ImGui::SetNextWindowFocus();
    }
    ImGui::Begin("Toolbar");
    const bool toolbarWasFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
    if (ctx.toolbarPanel)
    {
        ctx.toolbarPanel->render();
    }
    ImGui::End();

    // Optional bottom bar visibility controlled via preferences
    {
        bool showBottomBar = ctx.preferences ? ctx.preferences->safe_get({"ui", "show_bottom_bar"}, true) : true;
        if (showBottomBar)
        {
            ImGui::Begin("BottomBar");
            // ... bottom bar content ...
            ImGui::End();
        }
    }

    ImGui::Begin("Designer");
    if (ctx.visualWindow)
    {
        ctx.visualWindow->render();
    }
    ImGui::End();

    if (focusPackManager)
    {
        ImGui::SetNextWindowFocus();
    }
    ImGui::Begin("Pack Manager");
    const bool packManagerWasFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
    if (ctx.packManagerPanel)
    {
        ctx.packManagerPanel->render();
    }
    ImGui::End();

    if (focusPackViewer)
    {
        ImGui::SetNextWindowFocus();
    }
    ImGui::Begin("Pack Viewer");
    const bool packViewerWasFocused = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows);
    if (ctx.packViewerPanel)
    {
        ctx.packViewerPanel->render();
    }
    ImGui::End();

    // First-run prompt: if no packs installed, offer to install std_core
    if (noPacksInstalled && ctx.firstRunModal && !ctx.firstRunModal->isOpen() && !ctx.firstRunModal->isDismissed())
    {
        ctx.firstRunModal->open();
    }
    if (ctx.firstRunModal)
    {
        ctx.firstRunModal->render();
        // If the modal signaled a request to focus the Pack Manager (after install or skip), apply it once.
        if (ctx.firstRunModal->shouldFocusPackManager())
        {
            // Force focus next frame by setting savedLeftTab; also immediate focus this frame if possible
            if (savedLeftTab != "Pack Manager")
            {
                savedLeftTab = "Pack Manager";
                ctx.stateStore.saveLastLeftTab(savedLeftTab);
            }
            // Set next window focus for Pack Manager (will apply next frame since window already ended this frame)
            ImGui::FocusWindow(ImGui::FindWindowByName("Pack Manager"));
            ctx.firstRunModal->clearFocusRequest();
        }
    }

    // Mark focus decision as applied to avoid stealing focus every frame
    if (!didSetInitialFocus)
        didSetInitialFocus = true;

    // Persist last selected left tab when it changes based on which tab is focused
    // Save only on change to minimize file writes
    if (toolbarWasFocused && savedLeftTab != "Toolbar")
    {
        savedLeftTab = "Toolbar";
        ctx.stateStore.saveLastLeftTab(savedLeftTab);
    }
    else if (packManagerWasFocused && savedLeftTab != "Pack Manager")
    {
        savedLeftTab = "Pack Manager";
        ctx.stateStore.saveLastLeftTab(savedLeftTab);
    }
    else if (packViewerWasFocused && savedLeftTab != "Pack Viewer")
    {
        savedLeftTab = "Pack Viewer";
        ctx.stateStore.saveLastLeftTab(savedLeftTab);
    }

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