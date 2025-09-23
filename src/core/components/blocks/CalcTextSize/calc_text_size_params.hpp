#pragma once
#include <imgui.h>
#include <string>

struct CalcTextSizeParams {
    std::string text;
    std::string text_end;
    bool hide_text_after_double_hash;
    float wrap_width;
};
