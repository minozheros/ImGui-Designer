#include "ui/components/MainMenuBar.hpp"
#include "app/context/AppContext.hpp"
#include "app/state/LayoutStore.hpp"

#include <imgui.h>
#include <nlohmann/json.hpp>
#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>
#include "core/events/Events.hpp"

namespace ui::components
{

    void MainMenuBar::render()
    {
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                renderFileMenu();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("View"))
            {
                renderViewMenu();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Settings"))
            {
                renderSettingsMenu();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                renderHelpMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void MainMenuBar::renderFileMenu()
    {
        if (ImGui::MenuItem("New", "Ctrl+N"))
        {
            // TODO: implement new project/session. Placeholder.
            spdlog::info("File > New invoked");
        }
        if (ImGui::MenuItem("Open...", "Ctrl+O"))
        {
            // TODO: implement file dialog or project open
            spdlog::info("File > Open invoked");
        }
        if (ImGui::MenuItem("Save", "Ctrl+S"))
        {
            // TODO: implement save project/session
            spdlog::info("File > Save invoked");
        }
        if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
        {
            // TODO
            spdlog::info("File > Save As invoked");
        }
        ImGui::Separator();
        if (ImGui::MenuItem("Quit", "Ctrl+Q"))
        {
            spdlog::info("File > Quit invoked");
            ctx.dispatcher.trigger<core::QuitEvent<>>();
        }
    }

    void MainMenuBar::renderViewMenu()
    {
        // Layout actions: save/load/reset
        if (ImGui::MenuItem("Save Layout"))
        {
            app::state::LayoutStore store(ctx.designerCtx);
            if (store.saveDefaultLayout())
                spdlog::info("Saved layout to {}", app::state::LayoutStore::defaultLayoutPath());
            else
                spdlog::warn("Failed to save layout");
        }
        if (ImGui::MenuItem("Load Layout"))
        {
            app::state::LayoutStore store(ctx.designerCtx);
            if (store.loadDefaultLayout())
                spdlog::info("Loaded layout from {}", app::state::LayoutStore::defaultLayoutPath());
            else
                spdlog::warn("Failed to load layout");
        }
        if (ImGui::MenuItem("Reset Layout"))
        {
            app::state::LayoutStore store(ctx.designerCtx);
            store.resetLayoutToDefault();
            spdlog::info("Reset layout to default in-memory");
        }
    }

    void MainMenuBar::renderSettingsMenu()
    {
        // Simple toggle placeholder: show/hide BottomBar by preference flag
        bool showBottomBar = ctx.preferences ? ctx.preferences->safe_get({"ui", "show_bottom_bar"}, true) : true;
        if (ImGui::MenuItem("Show Bottom Bar", nullptr, showBottomBar))
        {
            if (ctx.preferences)
            {
                ctx.preferences->set("ui", nlohmann::json{{"show_bottom_bar", !showBottomBar}});
                ctx.preferences->save();
            }
        }
    }

    void MainMenuBar::renderHelpMenu()
    {
        if (ImGui::MenuItem("About"))
        {
            ImGui::OpenPopup("About ImGui-Designer");
        }
        if (ImGui::BeginPopupModal("About ImGui-Designer", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::TextUnformatted("ImGui-Designer\nA node-based UI designer using Dear ImGui.");
            ImGui::Separator();
            ImGui::TextUnformatted("Build info and versions are available in logs.");
            if (ImGui::Button("Close"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }
    }

} // namespace ui::components
