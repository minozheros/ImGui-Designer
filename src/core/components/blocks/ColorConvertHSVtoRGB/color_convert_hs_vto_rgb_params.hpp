#pragma once
#include <imgui.h>

struct ColorConvertHSVtoRGBParams {
    float h;
    float s;
    float v;
    float& out_r;
    float& out_g;
    float& out_b;
};
