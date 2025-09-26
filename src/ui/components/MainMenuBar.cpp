#include "ui/components/MainMenuBar.hpp"
#include "app/context/AppContext.hpp"
#include "app/state/LayoutStore.hpp"
#include "i18n/TranslationManager.hpp" // TR macro & TranslationManager
#include "i18n/TranslationManager.hpp" // Provides TR macro and TranslationManager singleton

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
            if (ImGui::BeginMenu(TR("menu.file").c_str()))
            {
                renderFileMenu();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu(TR("menu.view").c_str()))
            {
                renderViewMenu();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu(TR("menu.settings").c_str()))
            {
                renderSettingsMenu();
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu(TR("menu.help").c_str()))
            {
                renderHelpMenu();
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }
    }

    void MainMenuBar::renderFileMenu()
    {
        if (ImGui::MenuItem(TR("menu.file.new").c_str(), "Ctrl+N"))
        {
            ctx.projectService.newProject();
        }
        if (ImGui::MenuItem(TR("menu.file.open").c_str(), "Ctrl+O"))
        {
            // Placeholder: real implementation will open a file dialog. For now no-op.
            spdlog::info("File > Open selected (dialog not yet implemented)");
        }
        if (ImGui::MenuItem(TR("menu.file.save").c_str(), "Ctrl+S"))
        {
            if (!ctx.projectService.saveProject())
            {
                spdlog::info("File > Save fell back (likely requires Save As)");
            }
        }
        if (ImGui::MenuItem(TR("menu.file.save_as").c_str(), "Ctrl+Shift+S"))
        {
            // Placeholder: would prompt for path; we simulate a no-op.
            spdlog::info("File > Save As selected (dialog not yet implemented)");
        }
        ImGui::Separator();
        if (ImGui::MenuItem(TR("menu.file.quit").c_str(), "Ctrl+Q"))
        {
            spdlog::info("File > Quit invoked");
            ctx.dispatcher.trigger<core::QuitEvent<>>();
        }
    }

    void MainMenuBar::renderViewMenu()
    {
        // Layout actions: save/load/reset
        if (ImGui::MenuItem(TR("menu.view.save_layout").c_str()))
        {
            app::state::LayoutStore store(ctx.designerCtx);
            if (store.saveDefaultLayout())
                spdlog::info("Saved layout to {}", app::state::LayoutStore::defaultLayoutPath());
            else
                spdlog::warn("Failed to save layout");
        }
        if (ImGui::MenuItem(TR("menu.view.load_layout").c_str()))
        {
            app::state::LayoutStore store(ctx.designerCtx);
            if (store.loadDefaultLayout())
                spdlog::info("Loaded layout from {}", app::state::LayoutStore::defaultLayoutPath());
            else
                spdlog::warn("Failed to load layout");
        }
        if (ImGui::MenuItem(TR("menu.view.reset_layout").c_str()))
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
        if (ImGui::MenuItem(TR("menu.settings.show_bottom_bar").c_str(), nullptr, showBottomBar))
        {
            if (ctx.preferences)
            {
                ctx.preferences->set("ui", nlohmann::json{{"show_bottom_bar", !showBottomBar}});
                ctx.preferences->save();
            }
        }

        if (ImGui::BeginMenu(TR("menu.settings.language").c_str()))
        {
            std::string current = TranslationManager::instance().currentLanguage();
            struct Lang
            {
                const char *code;
                const char *label;
            } langs[] = {
                {"en", "English"},
                {"de", "Deutsch"}};
            for (const auto &l : langs)
            {
                bool selected = (current == l.code);
                if (ImGui::MenuItem(l.label, nullptr, selected))
                {
                    if (TranslationManager::instance().loadLanguage(l.code))
                    {
                        if (ctx.preferences)
                        {
                            ctx.preferences->set("ui", nlohmann::json{{"language", l.code}});
                            ctx.preferences->save();
                        }
                    }
                }
            }
            ImGui::EndMenu();
        }
    }

    void MainMenuBar::renderHelpMenu()
    {
        if (ImGui::MenuItem(TR("dialog.about.title").c_str()))
        {
            ImGui::OpenPopup(TR("dialog.about.title").c_str());
        }
        if (ImGui::BeginPopupModal(TR("dialog.about.title").c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::TextUnformatted(TR("dialog.about.body").c_str());
            ImGui::Separator();
            ImGui::TextUnformatted("Build info and versions are available in logs.");
            if (ImGui::Button("Close"))
                ImGui::CloseCurrentPopup();
            ImGui::EndPopup();
        }
    }

} // namespace ui::components
