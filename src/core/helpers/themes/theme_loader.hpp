#pragma once
#include <string>
#include <imgui.h>
#include <nlohmann/json.hpp>

namespace core
{
    // Loads a theme from a JSON file and applies it to ImGui::GetStyle().Colors
    void LoadAndApplyImGuiTheme(const std::string &filename);
}
