#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct TableHeadersRowParams {
    // No parameters


    std::vector<core::IParameterBase*> params;
    TableHeadersRowParams() {
    }
};
}
