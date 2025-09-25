#include "ui/panels/FirstRunModal.hpp"

#include <imgui.h>
#include <string>
#include <cstdlib>

namespace ui::panels
{

    void FirstRunModal::open()
    {
        if (dismissed_ || open_)
            return; // One-shot per session unless explicitly reset in future
        open_ = true;
        triedInstall_ = false;
        installing_ = false;
        installSucceeded_ = false;
        lastMessage_.clear();
        ImGui::OpenPopup("Welcome");
    }

    void FirstRunModal::render()
    {
        if (!open_ || dismissed_)
            return;

        bool keepOpen = true; // local state referencing openness this frame
        if (ImGui::BeginPopupModal("Welcome", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings))
        {
            ImGui::TextWrapped("No packs are installed yet. The official Standard Core pack provides classes, structs, enums, and basic C++ codegen. It's recommended to install it to get started.");
            ImGui::Separator();

            if (!triedInstall_)
            {
                if (ImGui::Button("Install Standard Core"))
                {
                    // Synchronous shell-out for now; could be threaded later.
                    installing_ = true;
                    std::string cmd = "python3 scripts/fetch_packs.py --index registry/packs.official.json --force --only package.std_core";
                    int rc = std::system(cmd.c_str());
                    installing_ = false;
                    triedInstall_ = true;
                    installSucceeded_ = (rc == 0);
                    lastMessage_ = installSucceeded_ ? "Installation completed. You can close this dialog." : "Installation failed. Check logs and try again via Pack Manager.";
                    if (installSucceeded_)
                    {
                        // After successful installation, request focus shift to Pack Manager
                        requestFocusPackManager_ = true;
                    }
                }
                ImGui::SameLine();
                if (ImGui::Button("Skip"))
                {
                    dismissed_ = true;
                    requestFocusPackManager_ = true; // User skipped; direct them to Pack Manager
                    keepOpen = false;
                }
            }
            else
            {
                ImGui::TextWrapped("%s", lastMessage_.c_str());
                ImGui::Spacing();
                if (ImGui::Button("Close"))
                {
                    dismissed_ = true;
                    // Even if install failed, still guide user toward Pack Manager for manual actions
                    requestFocusPackManager_ = true;
                    keepOpen = false;
                }
            }

            ImGui::EndPopup();
        }
        else
        {
            // Popup not actually open (e.g. lost focus); treat as closed.
            keepOpen = false;
        }

        if (!keepOpen)
        {
            ImGui::CloseCurrentPopup();
            open_ = false;
        }
    }

} // namespace ui::panels
