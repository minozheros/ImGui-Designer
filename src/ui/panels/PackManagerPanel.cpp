#include "ui/panels/PackManagerPanel.hpp"
#include "app/packs/PackIndexLoader.hpp"

#include <imgui.h>
#include <string>
#include <cstdlib>
#include <filesystem>

namespace ui::panels
{

    void PackManagerPanel::render()
    {
        if (!ImGui::Begin("Pack Manager"))
        {
            ImGui::End();
            return;
        }

        const std::filesystem::path root = std::filesystem::current_path();
        auto idx = app::packs::loadFromFile("registry/packs.official.json");
        if (!idx.has_value())
        {
            ImGui::TextUnformatted("No official pack index found (registry/packs.official.json)");
            ImGui::End();
            return;
        }

        ImGui::Text("Index version: %s", idx->version.c_str());
        if (!idx->updatedAt.empty())
            ImGui::Text("Updated: %s", idx->updatedAt.c_str());
        ImGui::Separator();

        for (const auto &e : idx->entries)
        {
            if (!e.enabled)
                continue;
            ImGui::PushID(e.id.c_str());
            ImGui::Text("%s (%s)", e.id.c_str(), e.kind.c_str());
            if (!e.description.empty())
                ImGui::TextWrapped("%s", e.description.c_str());
            ImGui::Text("repo: %s@%s", e.repo.c_str(), e.ref.c_str());
            if (ImGui::Button("Install"))
            {
                // For now, shell out to the Python fetcher.
                // This keeps it simple and reuses validation logic. Later we can replace with native HTTP.
                std::string cmd = "python3 scripts/fetch_packs.py --index registry/packs.official.json --force";
                std::ignore = std::system(cmd.c_str());
            }
            ImGui::Separator();
            ImGui::PopID();
        }

        ImGui::End();
    }

} // namespace ui::panels
