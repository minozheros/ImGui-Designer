#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetFontParams : public core::IParameterParamsBase {
    ParameterBase<ImFont*> return_value = ParameterBase<ImFont*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetFontParams() {
        params.push_back(&return_value);
    }
};
}
