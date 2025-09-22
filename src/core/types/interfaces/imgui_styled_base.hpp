// Shared base class for style and font logic
#pragma once
#include <nlohmann/json.hpp>
#include <imgui.h>
#include <string>
#include <vector>
#include <memory>

namespace core
{
    class ImGuiStyledBase
    {
    public:
        explicit ImGuiStyledBase(const nlohmann::json &config) : config_(config) {}
        virtual ~ImGuiStyledBase() = default;

    protected:
        // Style management for ImGui
        void applyStyleFromConfig(const nlohmann::json &config)
        {
            pushedStyleVars_.clear();
            pushedStyleColors_.clear();
            static const std::unordered_map<std::string, std::pair<ImGuiStyleVar, int>> styleVarMap = {
                {"alpha", {ImGuiStyleVar_Alpha, 0}},
                {"window_padding", {ImGuiStyleVar_WindowPadding, 1}},
                {"window_rounding", {ImGuiStyleVar_WindowRounding, 0}},
                {"window_border_size", {ImGuiStyleVar_WindowBorderSize, 0}},
                {"window_min_size", {ImGuiStyleVar_WindowMinSize, 1}},
                {"child_rounding", {ImGuiStyleVar_ChildRounding, 0}},
                {"child_border_size", {ImGuiStyleVar_ChildBorderSize, 0}},
                {"popup_rounding", {ImGuiStyleVar_PopupRounding, 0}},
                {"popup_border_size", {ImGuiStyleVar_PopupBorderSize, 0}},
                {"frame_padding", {ImGuiStyleVar_FramePadding, 1}},
                {"frame_rounding", {ImGuiStyleVar_FrameRounding, 0}},
                {"frame_border_size", {ImGuiStyleVar_FrameBorderSize, 0}},
                {"item_spacing", {ImGuiStyleVar_ItemSpacing, 1}},
                {"item_inner_spacing", {ImGuiStyleVar_ItemInnerSpacing, 1}},
                {"indent_spacing", {ImGuiStyleVar_IndentSpacing, 0}},
                {"cell_padding", {ImGuiStyleVar_CellPadding, 1}},
                {"scrollbar_size", {ImGuiStyleVar_ScrollbarSize, 0}},
                {"scrollbar_rounding", {ImGuiStyleVar_ScrollbarRounding, 0}},
                {"grab_min_size", {ImGuiStyleVar_GrabMinSize, 0}},
                {"grab_rounding", {ImGuiStyleVar_GrabRounding, 0}},
                {"tab_rounding", {ImGuiStyleVar_TabRounding, 0}},
                {"button_text_align", {ImGuiStyleVar_ButtonTextAlign, 1}},
                {"selectable_text_align", {ImGuiStyleVar_SelectableTextAlign, 1}}};
            if (config.contains("style_vars"))
            {
                for (auto it = config["style_vars"].begin(); it != config["style_vars"].end(); ++it)
                {
                    std::string key = it.key();
                    auto found = styleVarMap.find(key);
                    if (found != styleVarMap.end())
                    {
                        ImGuiStyleVar var = found->second.first;
                        int type = found->second.second; // 0=float, 1=ImVec2
                        if (type == 0)
                        {
                            float value = it.value();
                            ImGui::PushStyleVar(var, value);
                            pushedStyleVars_.push_back(var);
                        }
                        else if (type == 1)
                        {
                            if (it.value().is_array() && it.value().size() == 2)
                            {
                                float v0 = it.value()[0];
                                float v1 = it.value()[1];
                                ImGui::PushStyleVar(var, ImVec2(v0, v1));
                                pushedStyleVars_.push_back(var);
                            }
                            else
                            {
                                float value = it.value();
                                ImGui::PushStyleVar(var, ImVec2(value, value));
                                pushedStyleVars_.push_back(var);
                            }
                        }
                    }
                }
            }
            // Only config colors supported here (theme logic can be added by derived class)
            if (config.contains("colors"))
            {
                for (auto it = config["colors"].begin(); it != config["colors"].end(); ++it)
                {
                    std::string key = it.key();
                    std::string hex = it.value();
                    ImVec4 color = ImVec4(1, 1, 1, 1); // default white
                    if (hex.size() == 7 && hex[0] == '#')
                    {
                        int r = std::stoi(hex.substr(1, 2), nullptr, 16);
                        int g = std::stoi(hex.substr(3, 2), nullptr, 16);
                        int b = std::stoi(hex.substr(5, 2), nullptr, 16);
                        color = ImVec4(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
                    }
                    // Only a few color keys for now
                    if (key == "button")
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, color);
                        pushedStyleColors_.push_back(ImGuiCol_Button);
                    }
                    else if (key == "text")
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, color);
                        pushedStyleColors_.push_back(ImGuiCol_Text);
                    }
                }
            }
        }

        void popStyleFromConfig()
        {
            for (size_t i = 0; i < pushedStyleColors_.size(); ++i)
                ImGui::PopStyleColor();
            for (size_t i = 0; i < pushedStyleVars_.size(); ++i)
                ImGui::PopStyleVar();
            pushedStyleVars_.clear();
            pushedStyleColors_.clear();
        }

        // Font push/pop logic
        ImFont *pushFontFromConfig()
        {
            ImFont *useFont = nullptr;
            float fontSize = 0.0f;
            if (config_.contains("font"))
            {
                std::string fontName = config_["font"];
                fontSize = config_.value("font_size", 0.0f);
                for (auto *font : ImGui::GetIO().Fonts->Fonts)
                {
                    if (font->GetDebugName() && std::string(font->GetDebugName()) == fontName)
                    {
                        useFont = font;
                        break;
                    }
                }
                if (useFont)
                {
                    if (fontSize > 0.0f)
                        ImGui::PushFont(useFont, fontSize);
                    else
                        ImGui::PushFont(useFont);
                }
            }
            return useFont;
        }
        void popFontIfUsed(ImFont *useFont)
        {
            if (useFont)
                ImGui::PopFont();
        }

        const nlohmann::json &getConfig() const { return config_; }

    protected:
        nlohmann::json config_;
        std::vector<ImGuiStyleVar> pushedStyleVars_;
        std::vector<ImGuiCol> pushedStyleColors_;
    };
} // namespace core