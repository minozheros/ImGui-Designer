#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct CalcTextSizeParams {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);
    ParameterBase<const char*> text_end = ParameterBase<const char*>("text_end", ParameterType::INPUT);
    ParameterBase<bool> hide_text_after_double_hash = ParameterBase<bool>("hide_text_after_double_hash", ParameterType::INPUT);
    ParameterBase<float> wrap_width = ParameterBase<float>("wrap_width", ParameterType::INPUT);
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    CalcTextSizeParams() = default;
};
