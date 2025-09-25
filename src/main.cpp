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
#include "i18n/TranslationManager.hpp"
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

namespace core
{
    std::atomic<bool> running{true};
}

namespace
{
    void print_usage(const char *argv0)
    {
        spdlog::info("Usage: {} [options] [config_path]", argv0);
        spdlog::info("Options:");
        spdlog::info("  -v, --verbose           Set log level to debug (overrides preferences)");
        spdlog::info("      --trace              Set log level to trace (highest verbosity)");
        spdlog::info("      --log-level=LEVEL    Explicit log level (trace|debug|info|warn|error|critical|off)");
        spdlog::info("      --help               Show this help and exit");
        spdlog::info("Environment:");
        spdlog::info("  IMGDESIGNER_LOG_LEVEL   If set, used as log level unless --log-level/--trace/--verbose provided");
    }

    std::optional<spdlog::level::level_enum> level_from_string(const std::string &s)
    {
        try
        {
            return spdlog::level::from_str(s);
        }
        catch (...)
        {
            return std::nullopt; // from_str can throw for invalid input in some versions
        }
    }
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

    // --- CLI argument parsing (lightweight) ---
    // Pre-parse for our flags; allow either options first or after config path.
    bool flag_verbose = false;
    bool flag_trace = false;
    std::optional<std::string> explicit_level; // from --log-level
    bool show_help = false;

    std::vector<std::string> positional;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-v" || arg == "--verbose")
        {
            flag_verbose = true;
            continue;
        }
        if (arg == "--trace")
        {
            flag_trace = true;
            continue;
        }
        if (arg.rfind("--log-level=", 0) == 0)
        {
            explicit_level = arg.substr(std::string("--log-level=").size());
            continue;
        }
        if (arg == "--help" || arg == "-h")
        {
            show_help = true;
            continue;
        }
        if (!arg.empty() && arg[0] == '-')
        {
            spdlog::warn("Unknown option '{}' (ignored)", arg);
            continue;
        }
        positional.push_back(arg);
    }

    if (show_help)
    {
        print_usage(argv[0]);
        SDL_Quit();
        return 0;
    }

    if (!positional.empty())
    {
        // First positional argument = config path override.
        configPath = positional.front();
        spdlog::info("Config path overridden by command-line argument: {}", configPath);
    }
    else
    {
        spdlog::info("Loading preferences from: {}", configPath);
    }

    auto preferences = std::make_shared<Preferences>(configPath);

    // Determine log level precedence:
    // 1. --trace
    // 2. --verbose
    // 3. --log-level=LEVEL
    // 4. IMGDESIGNER_LOG_LEVEL env var
    // 5. preferences (logging.level)
    // 6. fallback 'info'
    std::string pref_level = preferences->safe_get({"logging", "level"}, std::string("info"));
    std::string chosen_level_str = pref_level;

    if (const char *env_lvl = std::getenv("IMGDESIGNER_LOG_LEVEL"))
    {
        if (env_lvl[0] != '\0')
            chosen_level_str = env_lvl;
    }
    if (explicit_level)
        chosen_level_str = *explicit_level;
    if (flag_verbose)
        chosen_level_str = "debug";
    if (flag_trace)
        chosen_level_str = "trace";

    if (auto lvl = level_from_string(chosen_level_str))
    {
        spdlog::set_level(*lvl);
        spdlog::info("Logging level set to {} (resolved via precedence)", chosen_level_str);
    }
    else
    {
        spdlog::warn("Invalid log level '{}', defaulting to info", chosen_level_str);
        spdlog::set_level(spdlog::level::info);
    }

    spdlog::info("Creating AppContext and MainFactory");
    AppContext ctx = AppContext();
    ctx.factories = std::make_unique<Factories>(&ctx);
    ctx.preferences = preferences;
    ctx.visualWindow = std::make_unique<VisualWindow>();
    ctx.toolbarPanel = std::make_unique<ToolbarPanel>(ctx);
    ctx.packManagerPanel = std::make_unique<ui::panels::PackManagerPanel>();
    ctx.packViewerPanel = std::make_unique<ui::panels::PackViewerPanel>();
    ctx.firstRunModal = std::make_unique<ui::panels::FirstRunModal>();
    ctx.dockingManager = std::make_unique<DockingManager>();
    ctx.mainMenuBar = std::make_unique<ui::components::MainMenuBar>(ctx);
    auto &dispatcher = ctx.dispatcher;
    dispatcher.sink<core::QuitEvent<>>().connect<&core::on_quit>();

    // Initialize translations (load preferred language; default 'en')
    std::string prefLang = preferences->safe_get({"ui", "language"}, std::string("en"));
    if (!TranslationManager::instance().loadLanguage(prefLang))
    {
        spdlog::warn("Falling back to English translations");
        TranslationManager::instance().loadLanguage("en");
    }

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
    // Wire context-dependent helpers
    ctx.layoutStore.setContext(ctx.designerCtx);
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
    SDL_GL_DestroyContext(ctx.glContext);
    SDL_DestroyWindow(ctx.designerWindow);
    SDL_Quit();
    return 0;
}
