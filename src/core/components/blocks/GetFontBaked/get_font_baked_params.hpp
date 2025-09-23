#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct GetFontBakedParams : public core::IParameterParamsBase {
    ParameterBase<ImFontBaked*> return_value = ParameterBase<ImFontBaked*>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    GetFontBakedParams() {
        params.push_back(&return_value);
    }
};
}
