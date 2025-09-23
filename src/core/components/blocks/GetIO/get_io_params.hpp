#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct GetIOParams {
    ParameterBase<ImGuiIO&> return_value = ParameterBase<ImGuiIO&>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetIOParams() {
        params.push_back(&return_value);
    }
};
}
