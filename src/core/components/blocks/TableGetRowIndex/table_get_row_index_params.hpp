#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct TableGetRowIndexParams {
    ParameterBase<int> return_value = ParameterBase<int>("return_value", ParameterType::RETURN);

    TableGetRowIndexParams() = default;
};
