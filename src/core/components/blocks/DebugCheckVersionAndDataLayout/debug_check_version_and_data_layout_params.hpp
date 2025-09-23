#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct DebugCheckVersionAndDataLayoutParams {
    ParameterBase<const char*> version_str = ParameterBase<const char*>("version_str", ParameterType::INPUT);
    ParameterBase<size_t> sz_io = ParameterBase<size_t>("sz_io", ParameterType::INPUT);
    ParameterBase<size_t> sz_style = ParameterBase<size_t>("sz_style", ParameterType::INPUT);
    ParameterBase<size_t> sz_vec2 = ParameterBase<size_t>("sz_vec2", ParameterType::INPUT);
    ParameterBase<size_t> sz_vec4 = ParameterBase<size_t>("sz_vec4", ParameterType::INPUT);
    ParameterBase<size_t> sz_drawvert = ParameterBase<size_t>("sz_drawvert", ParameterType::INPUT);
    ParameterBase<size_t> sz_drawidx = ParameterBase<size_t>("sz_drawidx", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    DebugCheckVersionAndDataLayoutParams() {
        params.push_back(&version_str);
        params.push_back(&sz_io);
        params.push_back(&sz_style);
        params.push_back(&sz_vec2);
        params.push_back(&sz_vec4);
        params.push_back(&sz_drawvert);
        params.push_back(&sz_drawidx);
        params.push_back(&return_value);
    }
};
}
