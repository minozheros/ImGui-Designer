#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
#include <imgui_internal.h>
#include <string>
#include <vector>
#include "ui/components/VisualWindow.hpp"
// #include "node/blocks/BeginCombo/begin_combo_node.hpp"
// #include "node/blocks/BeginCombo/begin_combo_params.hpp"

struct AppContext;

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