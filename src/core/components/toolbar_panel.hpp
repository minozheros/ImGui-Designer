#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <string>
#include <vector>
#include "core/components/visual_window.hpp"
#include "core/components/blocks/BeginCombo/begin_combo_node.hpp"
#include "core/components/blocks/BeginCombo/begin_combo_params.hpp"

struct AppContext;

namespace core
{
    class ToolbarPanel
    {
    public:
        ToolbarPanel(AppContext &appCtx);
        void render();
        static std::string toLower(const std::string &s);

    private:
        std::string nodeSearch;
        char searchBuffer[128] = "";
        std::vector<std::string> allNodes;
        AppContext &appContext;
    };
}