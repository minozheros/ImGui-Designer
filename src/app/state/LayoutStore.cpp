#include "app/state/LayoutStore.hpp"

#include <imgui.h>
#include <imgui_internal.h>
#include <fstream>
#include <filesystem>

namespace app::state
{

    static std::string kDefaultLayoutFile = "registry/layout.ini";

    std::string LayoutStore::defaultLayoutPath()
    {
        return kDefaultLayoutFile;
    }

    bool LayoutStore::saveLayoutToFile(const std::string &path) const
    {
        if (!imguiCtx)
            return false;
        ImGuiContext *prev = ImGui::GetCurrentContext();
        if (prev != imguiCtx)
            ImGui::SetCurrentContext(imguiCtx);

        // Build ini data
        ImGuiContext &g = *imguiCtx;
        ImGuiSettingsHandler *ini_handler = ImGui::FindSettingsHandler("Window");
        (void)ini_handler; // Using top-level API below; keep for reference

        size_t out_size = 0;
        const char *ini_data = ImGui::SaveIniSettingsToMemory(&out_size);
        if (!ini_data || out_size == 0)
        {
            if (prev != imguiCtx)
                ImGui::SetCurrentContext(prev);
            return false;
        }
        std::ofstream ofs(path, std::ios::binary);
        if (!ofs.is_open())
        {
            if (prev != imguiCtx)
                ImGui::SetCurrentContext(prev);
            return false;
        }
        ofs.write(ini_data, static_cast<std::streamsize>(out_size));
        ofs.close();
        // Note: Do not free ini_data; owned by ImGui until next call or context destruction.

        if (prev != imguiCtx)
            ImGui::SetCurrentContext(prev);
        return true;
    }

    bool LayoutStore::loadLayoutFromFile(const std::string &path) const
    {
        if (!imguiCtx)
            return false;
        if (!std::filesystem::exists(path))
            return false;
        ImGuiContext *prev = ImGui::GetCurrentContext();
        if (prev != imguiCtx)
            ImGui::SetCurrentContext(imguiCtx);

        std::ifstream ifs(path, std::ios::binary);
        if (!ifs.is_open())
        {
            if (prev != imguiCtx)
                ImGui::SetCurrentContext(prev);
            return false;
        }
        std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
        ifs.close();

        ImGui::LoadIniSettingsFromMemory(content.c_str(), content.size());

        if (prev != imguiCtx)
            ImGui::SetCurrentContext(prev);
        return true;
    }

    void LayoutStore::resetLayoutToDefault() const
    {
        if (!imguiCtx)
            return;
        ImGuiContext *prev = ImGui::GetCurrentContext();
        if (prev != imguiCtx)
            ImGui::SetCurrentContext(imguiCtx);

        // Clear all windows/docking settings by feeding empty ini
        ImGui::LoadIniSettingsFromMemory("");

        if (prev != imguiCtx)
            ImGui::SetCurrentContext(prev);
    }

} // namespace app::state
