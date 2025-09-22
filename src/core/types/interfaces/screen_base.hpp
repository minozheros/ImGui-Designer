// Hook setters

#pragma once

#include <nlohmann/json.hpp>
#include <functional>
#include <memory>
#include <vector>
#include "core/factories/component_factory.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include "core/interfaces/imgui_styled_base.hpp"

namespace core
{

    class ScreenBase : public ImGuiStyledBase
    {
    public:
        using DrawFunc = std::function<void(ScreenBase *)>;

        explicit ScreenBase(const nlohmann::json &config, core::ComponentFactory *componentFactory = nullptr)
            : ImGuiStyledBase(config)
        {
            // Parse window_flags from config if present
            windowFlags_ = ImGuiWindowFlags_None;
            if (config_.contains("window_flags"))
            {
                // window_flags can be an integer or array of strings
                if (config_["window_flags"].is_number_integer())
                {
                    windowFlags_ = config_["window_flags"].get<int>();
                }
                else if (config_["window_flags"].is_array())
                {
                    for (const auto &flag : config_["window_flags"])
                    {
                        if (flag.is_string())
                        {
                            windowFlags_ |= parseFlag(flag.get<std::string>());
                        }
                    }
                }
                else if (config_["window_flags"].is_string())
                {
                    windowFlags_ = parseFlag(config_["window_flags"].get<std::string>());
                }
            }
            // Instantiate components from config if present
            if (componentFactory && config_.contains("components") && config_["components"].is_array())
            {
                for (const auto &compConf : config_["components"])
                {
                    auto comp = componentFactory->createComponent(compConf);
                    if (comp)
                        components_.push_back(comp);
                }
            }
        }

        virtual ~ScreenBase() = default;

        virtual void draw()
        {
            bool visible = config_.value("visible", true);
            if (!visible)
                return;

            if (preDrawHook_)
                preDrawHook_(this);

            if (config_.contains("pos") && config_.contains("size"))
            {
                ImGui::SetNextWindowPos(ImVec2(config_["pos"][0], config_["pos"][1]));
                ImGui::SetNextWindowSize(ImVec2(config_["size"][0], config_["size"][1]));
            }

            applyStyleFromConfig(config_);
            ImFont *useFont = pushFontFromConfig();

            ImGui::Begin(config_.value("title", "Screen").c_str(), nullptr, windowFlags_);

            // Draw all components
            for (auto &comp : components_)
            {
                if (comp)
                    comp->draw();
            }

            if (drawFunc_)
                drawFunc_(this);

            ImGui::End();

            popFontIfUsed(useFont);
            popStyleFromConfig();

            if (postDrawHook_)
                postDrawHook_(this);
        }

        ImGuiWindowFlags parseFlag(const std::string &flag)
        {
            if (flag == "NoTitleBar")
                return ImGuiWindowFlags_NoTitleBar;
            if (flag == "NoResize")
                return ImGuiWindowFlags_NoResize;
            if (flag == "NoMove")
                return ImGuiWindowFlags_NoMove;
            if (flag == "NoScrollbar")
                return ImGuiWindowFlags_NoScrollbar;
            if (flag == "NoScrollWithMouse")
                return ImGuiWindowFlags_NoScrollWithMouse;
            if (flag == "NoCollapse")
                return ImGuiWindowFlags_NoCollapse;
            if (flag == "AlwaysAutoResize")
                return ImGuiWindowFlags_AlwaysAutoResize;
            if (flag == "NoBackground")
                return ImGuiWindowFlags_NoBackground;
            if (flag == "NoSavedSettings")
                return ImGuiWindowFlags_NoSavedSettings;
            if (flag == "MenuBar")
                return ImGuiWindowFlags_MenuBar;
            // Add more as needed
            return ImGuiWindowFlags_None;
        }

        void setDrawFunc(DrawFunc func) { drawFunc_ = std::move(func); }
        const nlohmann::json &getConfig() const { return config_; }
        void setPreDrawHook(DrawFunc func) { preDrawHook_ = std::move(func); }
        void setPostDrawHook(DrawFunc func) { postDrawHook_ = std::move(func); }

    protected:
        std::vector<std::shared_ptr<core::ComponentBase>> components_;
        DrawFunc drawFunc_;
        DrawFunc preDrawHook_;
        DrawFunc postDrawHook_;
        ImGuiWindowFlags windowFlags_ = ImGuiWindowFlags_None;
    };

}