#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct CalcTextSizeParams : public core::IParameterParamsBase {
    ParameterBase<const char*> text = ParameterBase<const char*>("text", ParameterType::INPUT);
    ParameterBase<const char*> text_end = ParameterBase<const char*>("text_end", ParameterType::INPUT);
    ParameterBase<bool> hide_text_after_double_hash = ParameterBase<bool>("hide_text_after_double_hash", ParameterType::INPUT);
    ParameterBase<float> wrap_width = ParameterBase<float>("wrap_width", ParameterType::INPUT);
    ParameterBase<ImVec2> return_value = ParameterBase<ImVec2>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    CalcTextSizeParams() {
        params.push_back(&text);
        params.push_back(&text_end);
        params.push_back(&hide_text_after_double_hash);
        params.push_back(&wrap_width);
        params.push_back(&return_value);
    }
};
}
