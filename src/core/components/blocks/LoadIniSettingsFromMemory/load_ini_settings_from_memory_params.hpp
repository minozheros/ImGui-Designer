#pragma once
#include <imgui.h>
#include <string>

struct LoadIniSettingsFromMemoryParams {
    std::string ini_data;
    size_t ini_size;
};
