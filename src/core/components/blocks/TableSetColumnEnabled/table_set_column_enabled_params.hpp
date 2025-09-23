#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct TableSetColumnEnabledParams : public core::IParameterParamsBase {
    ParameterBase<int> column_n = ParameterBase<int>("column_n", ParameterType::INPUT);
    ParameterBase<bool> v = ParameterBase<bool>("v", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    TableSetColumnEnabledParams() {
        params.push_back(&column_n);
        params.push_back(&v);
    }
};
}
