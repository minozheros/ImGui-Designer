#define IMGUI_DEFINE_MATH_OPERATORS
#include <SDL3/SDL.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"
#include "RuntimeObjectSystem/RuntimeObjectSystem.h"
#include <spdlog/spdlog.h>
#include <entt/entt.hpp>

#include "core/events/Events.hpp"
#include "core/types/internal/SystemArchitecture.hpp"
#include <csignal>
#include <cstdint>
#include <atomic>

#include <memory>
#include "ui/rendering/SpdlogDedup.hpp"
#include <magic_enum.hpp>

#include "ui/rendering/RenderImGuiDesignerWindow.hpp"
#include "ui/rendering/InitImGuiContext.hpp"
#include "ui/rendering/WindowDestruction.hpp"
#include "ui/components/VisualWindow.hpp"
#include "ui/docking/DockingManager.hpp"
#include <atomic>

namespace core
{
    std::atomic<bool> running{true};
}

int main(int argc, char *argv[])
{
    RuntimeObjectSystem rccppSystem;
    rccppSystem.Initialise(nullptr, nullptr);

    // Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        spdlog::error("Failed to initialize SDL: {}", SDL_GetError());
        return -1;
    }

    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SpdlogDedupGlobal::setup_global_logger();

    std::signal(SIGINT, core::signalHandler);
    std::string configPath = "config/config.json";
    if (argc > 1)
    {
        configPath = argv[1];
        spdlog::info("Config path overridden by command-line argument: {}", configPath);
    }
    else
    {
        spdlog::info("Loading preferences from: {}", configPath);
    }
    auto preferences = std::make_shared<Preferences>(configPath);

    auto level = preferences->safe_get({"logging", "level"}, std::string("info"));

    spdlog::set_level(spdlog::level::from_str(level));
    spdlog::info("Logging level set to {}", level);
    spdlog::info("Creating AppContext and MainFactory");
    AppContext ctx = AppContext();
    // Register all visual blocks for the node editor sidebar
    // extern void registerAllVisualBlocks();
    // registerAllVisualBlocks();
    ctx.factories = std::make_unique<Factories>(&ctx);
    ctx.preferences = preferences;
    ctx.visualWindow = std::make_unique<VisualWindow>();
    ctx.toolbarPanel = std::make_unique<ToolbarPanel>(ctx);
    ctx.dockingManager = std::make_unique<DockingManager>();
    auto &dispatcher = ctx.dispatcher;
    dispatcher.sink<core::QuitEvent<>>().connect<&core::on_quit>();

    spdlog::debug("Setting up windows and renderers");
    ctx.designerWindow = SDL_CreateWindow("ImGui-Designer", 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
    if (!ctx.designerWindow)
    {
        spdlog::error("Failed to create SDL window: {}", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Create OpenGL context
    ctx.glContext = SDL_GL_CreateContext(ctx.designerWindow);
    if (!ctx.glContext)
    {
        spdlog::error("Failed to create OpenGL context: {}", SDL_GetError());
        SDL_DestroyWindow(ctx.designerWindow);
        SDL_Quit();
        return -1;
    }

    // Make context current
    SDL_GL_MakeCurrent(ctx.designerWindow, ctx.glContext);

    spdlog::debug("Windows and renderers set up successfully");

    // --- ImGui initialization ---
    spdlog::debug("Initializing ImGui context");
    IMGUI_CHECKVERSION();

    if (InitImGuiContext(ctx.designerCtx, ctx.designerWindow) != 0)
    {
        spdlog::error("Failed to initialize main ImGui context");
        SDL_GL_DestroyContext(ctx.glContext);
        SDL_DestroyWindow(ctx.designerWindow);
        SDL_Quit();
        return -1;
    }
    spdlog::debug("ImGui context initialized successfully");
    const int target_fps = ctx.preferences->safe_get({"performance", "target_fps"}, 25);
    const double frame_delay = 1.0 / target_fps;
    spdlog::debug("Entering main loop");
    while (core::running)
    {
        double frame_start = SDL_GetTicksNS() / 1000000000.0;

        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                core::running = false;
            }
        }

        // RENDER MAIN CTX (now also calls draw actions)
        RenderDesignerWindow(ctx, ctx.designerCtx, ctx.designerWindow);

        rccppSystem.GetFileChangeNotifier()->Update(0.0f);
        double frame_end = SDL_GetTicksNS() / 1000000000.0;
        double elapsed = frame_end - frame_start;
        if (elapsed < frame_delay)
        {
            SDL_DelayNS(static_cast<Uint64>((frame_delay - elapsed) * 1000000000.0));
        }
    }

    spdlog::debug("Main loop exited, triggering QuitEvent");
    dispatcher.trigger<core::QuitEvent<>>();

    spdlog::debug("Destroying windows and renderers");
    if (WindowDestruction(ctx.designerCtx, ctx.designerWindow, ctx.glContext) != 0)
    {
        spdlog::error("Failed to destroy designer window and renderer");
        return -1;
    }
    else
    {
        spdlog::info("Successfully destroyed designer window and renderer");
    }
    spdlog::info("Application exited cleanly");
    return 0;
}
