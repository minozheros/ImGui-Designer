#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct ArrowButtonParams {
    ParameterBase<const char*> str_id = ParameterBase<const char*>("str_id", ParameterType::INPUT);
    ParameterBase<ImGuiDir> dir = ParameterBase<ImGuiDir>("dir", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    ArrowButtonParams() {
        params.push_back(&str_id);
        params.push_back(&dir);
        params.push_back(&return_value);
    }
};
}
