#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct TableHeadersRowParams : public core::IParameterParamsBase {
    // No parameters


    std::vector<core::IParameterBase*> params;
    TableHeadersRowParams() {
    }
};
}
