

#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include "core/interfaces/imgui_styled_base.hpp"
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <memory>
#include "core/components/value.hpp"
#include <entt/entt.hpp>

namespace core
{

    class ComponentBase : public ImGuiStyledBase
    {
    public:
        using Action = std::function<void(const nlohmann::json &)>;

        explicit ComponentBase(const nlohmann::json &config, entt::dispatcher &dispatcher, std::shared_ptr<nlohmann::json> theme = nullptr)
            : ImGuiStyledBase(config), dispatcher_(dispatcher), theme_(theme) {}
        virtual ~ComponentBase() = default;

        void setDrawFunc(std::function<void(ComponentBase *)> func) { drawFunc_ = std::move(func); }
        // Drawing interface

        virtual void draw()
        {
            auto visiblePtr = this->getValue<bool>("visible", true);
            bool visible = visiblePtr ? visiblePtr->get() : true;
            if (!visible)
                return;

            if (preDrawHook_)
                preDrawHook_(this);

            auto enabledPtr = this->getValue<bool>("enabled", true);
            bool enabled = enabledPtr ? enabledPtr->get() : true;
            if (!enabled)
                ImGui::BeginDisabled();

            applyStyleFromConfig(config_);
            auto alignmentPtr = this->getValue<std::string>("horizontalAlignment", "none");
            std::string alignment = alignmentPtr ? alignmentPtr->get() : "none";
            if (alignment != "none")
            {
                applyHorizontalAlignment(alignment);
            }
            auto verticalAlignmentPtr = this->getValue<std::string>("verticalAlignment", "none");
            std::string verticalAlignment = verticalAlignmentPtr ? verticalAlignmentPtr->get() : "none";
            if (verticalAlignment != "none")
                applyVerticalAlignment(verticalAlignment);

            ImFont *useFont = pushFontFromConfig();

            if (drawFunc_)
                drawFunc_(this);

            popFontIfUsed(useFont);
            popStyleFromConfig();
            if (!enabled)
                ImGui::EndDisabled();

            if (postDrawHook_)
                postDrawHook_(this);
        }

        // Public getter for the component's config
        const nlohmann::json &getConfig() const
        {
            return config_;
        }

        // State/value management using core::Value
        template <typename T>
        void setValue(const std::string &key, std::shared_ptr<core::Value<T>> value)
        {
            valueMap_[key] = value;
        }

        template <typename T>
        std::shared_ptr<core::Value<T>> getValue(const std::string &key, T defaultValue) const
        {
            auto it = valueMap_.find(key);
            if (it != valueMap_.end())
            {
                return std::static_pointer_cast<core::Value<T>>(it->second);
            }
            using Handler = std::function<T(T)>;
            return std::make_shared<core::Value<T>>(defaultValue, defaultValue, defaultValue, Handler{}, Handler{});
        }

        // Action/function management
        void addAction(const std::string &name, Action action)
        {
            actions_[name] = std::move(action);
        }
        void callAction(const std::string &name, const nlohmann::json &data = {})
        {
            auto it = actions_.find(name);
            if (it != actions_.end())
                it->second(data);
        }

        // Style management for ImGui
        void applyStyleFromConfig(const nlohmann::json &config)
        {
            pushedStyleVars_.clear();
            pushedStyleColors_.clear();
            // Map string keys to ImGuiStyleVar enums and type (float or ImVec2)
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
            // Prefer theme for colors, fallback to config["colors"]
            const nlohmann::json *colorSource = nullptr;
            if (theme_ && theme_->contains("colors"))
            {
                colorSource = &(*theme_)["colors"];
            }
            else if (config.contains("colors"))
            {
                colorSource = &config["colors"];
            }
            if (colorSource)
            {
                for (auto it = colorSource->begin(); it != colorSource->end(); ++it)
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
                    if (key == "button")
                    {
                        ImGui::PushStyleColor(ImGuiCol_Button, color);
                        pushedStyleColors_.push_back(ImGuiCol_Button);
                    }
                    else if (key == "text")
                    {
                        ImGui::PushStyleColor(ImGuiCol_Text, color);
                        pushedStyleColors_.push_back(ImGuiCol_Text);
                    } // Add more mappings as needed
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

        // Utility for horizontal alignment (left, center, right)
        void applyHorizontalAlignment(const std::string &label) const
        {
            if (!config_.contains("horizontal_alignment"))
                return;
            std::string align = config_["horizontal_alignment"];
            float avail = ImGui::GetContentRegionAvail().x;
            float itemWidth = ImGui::CalcTextSize(label.c_str()).x + ImGui::GetStyle().FramePadding.x * 2;
            if (align == "center")
            {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (avail - itemWidth) * 0.5f);
            }
            else if (align == "right")
            {
                ImGui::SetCursorPosX(ImGui::GetCursorPosX() + (avail - itemWidth));
            }
            // left is default, do nothing
        }

        // Utility for vertical alignment (top, center, bottom)
        void applyVerticalAlignment(const std::string &alignment) const
        {
            float avail = ImGui::GetContentRegionAvail().y;
            float itemHeight = avail;
            if (config_.contains("item_height"))
            {
                itemHeight = config_["item_height"];
            }

            if (alignment == "center")
            {
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (avail - itemHeight) * 0.5f);
            }
            else if (alignment == "bottom")
            {
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (avail - itemHeight));
            }
            // top is default, do nothing
        }

        // Hook setters
        void setPreDrawHook(std::function<void(ComponentBase *)> func) { preDrawHook_ = std::move(func); }
        void setPostDrawHook(std::function<void(ComponentBase *)> func) { postDrawHook_ = std::move(func); }

    protected:
        entt::dispatcher &dispatcher_;
        std::unordered_map<std::string, std::shared_ptr<void>> valueMap_;
        std::unordered_map<std::string, Action> actions_;
        std::shared_ptr<nlohmann::json> theme_;
        std::function<void(ComponentBase *)> drawFunc_;
        std::function<void(ComponentBase *)> preDrawHook_;
        std::function<void(ComponentBase *)> postDrawHook_;
    };

}