#define IMGUI_DEFINE_MATH_OPERATORS
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "RuntimeObjectSystem/RuntimeObjectSystem.h"
#include <spdlog/spdlog.h>
#include <entt/entt.hpp>

#include "core/events/events.hpp"
#include "core/types/internal/system_architecture.hpp"
#include <csignal>
#include <cstdint>
#include <atomic>

#include <memory>
#include "core/helpers/init/spdlog_dedup.hpp"
#include <magic_enum.hpp>
#include "core/helpers/init/window_setup.hpp"

#include "core/helpers/init/render_imgui_designer_window.hpp"
#include "core/helpers/init/init_imgui_context.hpp"
#include "core/helpers/init/window_destruction.hpp"
#include "core/components/visual_window.hpp"
#include <atomic>

    std::atomic<bool> core::running{true};

    

    int main(int argc, char *argv[])
    {
        RuntimeObjectSystem rccppSystem;
        rccppSystem.Initialise(nullptr, nullptr);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
        auto preferences = std::make_shared<core::Preferences>(configPath);

        auto level = preferences->safe_get({"logging", "level"}, std::string("info"));

        spdlog::set_level(spdlog::level::from_str(level));
        spdlog::info("Logging level set to {}", level);
        spdlog::info("Creating AppContext and MainFactory");
        AppContext ctx = AppContext();
        // Register all visual blocks for the node editor sidebar
        // extern void registerAllVisualBlocks();
        // registerAllVisualBlocks();
        ctx.factories = std::make_unique<core::Factories>(&ctx);
        ctx.preferences = preferences;

        auto &dispatcher = ctx.dispatcher;
        dispatcher.sink<core::QuitEvent<>>().connect<&core::on_quit>();

        spdlog::debug("Setting up windows and renderers");
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
        ctx.designerWindow = core::setup_glfw_window_and_opengl_context(800, 600, "ImGui-Designer");

        spdlog::debug("Windows and renderers set up successfully");

        // --- ImGui initialization ---
        spdlog::debug("Initializing ImGui context");
        IMGUI_CHECKVERSION();

        if (core::InitImGuiContext(ctx.designerCtx, ctx.designerWindow) != 0)
        {
            spdlog::error("Failed to initialize main ImGui context");
            return -1;
        }
        spdlog::debug("ImGui context initialized successfully");
        const int target_fps = ctx.preferences->safe_get({"performance", "target_fps"}, 25);
        const double frame_delay = 1.0 / target_fps;
        spdlog::debug("Entering main loop");
        while (!glfwWindowShouldClose(ctx.designerWindow) && core::running)
        {
            double frame_start = glfwGetTime();

            glfwPollEvents();

            

            // RENDER MAIN CTX (now also calls draw actions)
            core::RenderDesignerWindow(ctx, ctx.designerCtx, ctx.designerWindow);

            rccppSystem.GetFileChangeNotifier()->Update(0.0f);
            double frame_end = glfwGetTime();
            double elapsed = frame_end - frame_start;
            if (elapsed < frame_delay)
            {
                std::this_thread::sleep_for(std::chrono::duration<double>(frame_delay - elapsed));
            }
        }

        spdlog::debug("Main loop exited, triggering QuitEvent");
        dispatcher.trigger<core::QuitEvent<>>();

        spdlog::debug("Destroying windows and renderers");
        if (core::WindowDestruction(ctx.designerCtx, ctx.designerWindow) != 0)
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

