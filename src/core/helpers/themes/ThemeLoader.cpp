#include "core/helpers/themes/theme_loader.hpp"
#include <fstream>
#include <spdlog/spdlog.h>

namespace core
{

    void LoadAndApplyImGuiTheme(const std::string &filename)
    {
        std::ifstream file(filename);
        if (!file)
        {
            spdlog::warn("Could not open theme file: {}", filename);
            return;
        }
        nlohmann::json themeJson;
        try
        {
            file >> themeJson;
        }
        catch (const std::exception &e)
        {
            spdlog::warn("Failed to parse theme JSON: {}", e.what());
            return;
        }
        ImGuiStyle &style = ImGui::GetStyle();
        static const std::unordered_map<std::string, ImGuiCol_> colorNameToEnum = {
            {"ImGuiCol_Text", ImGuiCol_Text},
            {"ImGuiCol_WindowBg", ImGuiCol_WindowBg},
            {"ImGuiCol_Button", ImGuiCol_Button},
            {"ImGuiCol_ButtonHovered", ImGuiCol_ButtonHovered},
            {"ImGuiCol_ButtonActive", ImGuiCol_ButtonActive},
            {"ImGuiCol_FrameBg", ImGuiCol_FrameBg},
            {"ImGuiCol_FrameBgHovered", ImGuiCol_FrameBgHovered},
            {"ImGuiCol_FrameBgActive", ImGuiCol_FrameBgActive},
            {"ImGuiCol_TitleBg", ImGuiCol_TitleBg},
            {"ImGuiCol_TitleBgActive", ImGuiCol_TitleBgActive},
            {"ImGuiCol_TitleBgCollapsed", ImGuiCol_TitleBgCollapsed},
            {"ImGuiCol_CheckMark", ImGuiCol_CheckMark},
            {"ImGuiCol_SliderGrab", ImGuiCol_SliderGrab},
            {"ImGuiCol_SliderGrabActive", ImGuiCol_SliderGrabActive},
            {"ImGuiCol_Header", ImGuiCol_Header},
            {"ImGuiCol_HeaderHovered", ImGuiCol_HeaderHovered},
            {"ImGuiCol_HeaderActive", ImGuiCol_HeaderActive},
            {"ImGuiCol_Separator", ImGuiCol_Separator},
            {"ImGuiCol_SeparatorHovered", ImGuiCol_SeparatorHovered},
            {"ImGuiCol_SeparatorActive", ImGuiCol_SeparatorActive}
            // Add more as needed
        };

        // Load named colors if present
        std::unordered_map<std::string, ImVec4> namedColors;
        if (themeJson.contains("colors") && themeJson["colors"].is_object())
        {
            for (auto it = themeJson["colors"].begin(); it != themeJson["colors"].end(); ++it)
            {
                if (it.value().is_array() && it.value().size() == 4)
                {
                    namedColors[it.key()] = ImVec4(
                        it.value()[0].get<float>(),
                        it.value()[1].get<float>(),
                        it.value()[2].get<float>(),
                        it.value()[3].get<float>());
                }
            }
        }

        for (auto it = themeJson.begin(); it != themeJson.end(); ++it)
        {
            // skip the 'colors' object itself
            if (it.key() == "colors")
                continue;
            auto found = colorNameToEnum.find(it.key());
            if (found == colorNameToEnum.end())
                continue;
            int idx = found->second;
            ImVec4 color;
            if (it.value().is_array() && it.value().size() == 4)
            {
                color = ImVec4(
                    it.value()[0].get<float>(),
                    it.value()[1].get<float>(),
                    it.value()[2].get<float>(),
                    it.value()[3].get<float>());
            }
            else if (it.value().is_string())
            {
                std::string ref = it.value();
                auto named = namedColors.find(ref);
                if (named != namedColors.end())
                {
                    color = named->second;
                }
                else
                {
                    // fallback: white
                    color = ImVec4(1, 1, 1, 1);
                }
            }
            else
            {
                // fallback: white
                color = ImVec4(1, 1, 1, 1);
            }
            if (idx >= 0 && idx < ImGuiCol_COUNT)
            {
                style.Colors[idx] = color;
            }
        }
    }

} // namespace core
