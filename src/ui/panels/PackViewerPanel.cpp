#include "ui/panels/PackViewerPanel.hpp"

#include <imgui.h>
#include <nlohmann/json.hpp>
#include <fstream>

namespace ui::panels
{

    void PackViewerPanel::render()
    {
        if (!ImGui::Begin("Pack Viewer"))
        {
            ImGui::End();
            return;
        }
        nlohmann::json j;
        std::ifstream f("registry/packs.lock.json");
        if (!f.is_open())
        {
            ImGui::TextUnformatted("No lockfile found: registry/packs.lock.json");
            ImGui::End();
            return;
        }
        try
        {
            f >> j;
        }
        catch (...)
        {
            j = nlohmann::json{};
        }
        if (!j.contains("entries"))
        {
            ImGui::TextUnformatted("Lockfile is empty or missing 'entries'.");
            ImGui::End();
            return;
        }
        ImGui::Text("version: %s", j.value("version", "").c_str());
        ImGui::Separator();
        for (const auto &e : j["entries"])
        {
            const std::string id = e.value("id", "");
            const std::string kind = e.value("kind", "");
            const std::string repo = e.value("repo", "");
            const std::string ref = e.value("ref", "");
            const std::string dest = e.value("dest", "");
            const std::string sha = e.value("sha256", "");
            ImGui::Text("%s (%s)", id.c_str(), kind.c_str());
            ImGui::Text("%s@%s -> %s", repo.c_str(), ref.c_str(), dest.c_str());
            if (!sha.empty())
                ImGui::Text("sha256: %s", sha.c_str());
            ImGui::Separator();
        }
        ImGui::End();
    }

} // namespace ui::panels
