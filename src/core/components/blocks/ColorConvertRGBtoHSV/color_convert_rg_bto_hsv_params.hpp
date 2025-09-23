#pragma once
#include <imgui.h>

struct ColorConvertRGBtoHSVParams {
    float r;
    float g;
    float b;
    float& out_h;
    float& out_s;
    float& out_v;
};
