#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DebugCheckVersionAndDataLayoutParams {
    ParameterBase<const char*> version_str = ParameterBase<const char*>("version_str", ParameterType::INPUT);
    ParameterBase<size_t> sz_io = ParameterBase<size_t>("sz_io", ParameterType::INPUT);
    ParameterBase<size_t> sz_style = ParameterBase<size_t>("sz_style", ParameterType::INPUT);
    ParameterBase<size_t> sz_vec2 = ParameterBase<size_t>("sz_vec2", ParameterType::INPUT);
    ParameterBase<size_t> sz_vec4 = ParameterBase<size_t>("sz_vec4", ParameterType::INPUT);
    ParameterBase<size_t> sz_drawvert = ParameterBase<size_t>("sz_drawvert", ParameterType::INPUT);
    ParameterBase<size_t> sz_drawidx = ParameterBase<size_t>("sz_drawidx", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    DebugCheckVersionAndDataLayoutParams() = default;
};
