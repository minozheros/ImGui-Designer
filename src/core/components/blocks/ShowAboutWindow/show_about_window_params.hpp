#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct ShowAboutWindowParams : public core::IParameterParamsBase {
    ParameterBase<bool*> p_open = ParameterBase<bool*>("p_open", ParameterType::OUTPUT);

    std::vector<core::IParameterBase*> params;
    ShowAboutWindowParams() {
        params.push_back(&p_open);
    }
};
}
