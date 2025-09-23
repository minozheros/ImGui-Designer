#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableHeaderParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);

    TableHeaderParams() = default;
};
