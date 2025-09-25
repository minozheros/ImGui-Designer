#include "ui/panels/FirstRunModal.hpp"

#include <imgui.h>
#include <string>
#include <cstdlib>

namespace ui::panels
{

    void FirstRunModal::open()
    {
        open_ = true;
        triedInstall_ = false;
        lastMessage_.clear();
        ImGui::OpenPopup("Welcome");
    }

    void FirstRunModal::render()
    {
        if (!open_)
            return;
        bool pOpen = true;
        if (ImGui::BeginPopupModal("Welcome", &pOpen, ImGuiWindowFlags_AlwaysAutoResize))
        {
            ImGui::TextWrapped("No packs are installed yet. The official Standard Core pack provides classes, structs, enums, and basic C++ codegen. It's recommended to install it to get started.");
            if (!triedInstall_)
            {
                if (ImGui::Button("Install Standard Core"))
                {
                    // Reuse Python fetcher with --only for targeted install
                    std::string cmd = "python3 scripts/fetch_packs.py --index registry/packs.official.json --force --only package.std_core";
                    int rc = std::system(cmd.c_str());
                    triedInstall_ = true;
                    lastMessage_ = (rc == 0) ? "Installation completed. You can close this dialog." : "Installation failed. Check logs and try again via Pack Manager.";
                }
                ImGui::SameLine();
                if (ImGui::Button("Skip"))
                {
                    pOpen = false;
                }
            }
            else
            {
                ImGui::Separator();
                ImGui::TextWrapped("%s", lastMessage_.c_str());
                if (ImGui::Button("Close"))
                {
                    pOpen = false;
                }
            }
            ImGui::EndPopup();
        }
        if (!pOpen)
        {
            ImGui::CloseCurrentPopup();
            open_ = false;
        }
    }

} // namespace ui::panels
