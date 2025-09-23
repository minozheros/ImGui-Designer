#pragma once
#include <imgui.h>
#include <string>

struct DebugCheckVersionAndDataLayoutParams {
    std::string version_str;
    size_t sz_io;
    size_t sz_style;
    size_t sz_vec2;
    size_t sz_vec4;
    size_t sz_drawvert;
    size_t sz_drawidx;
};
