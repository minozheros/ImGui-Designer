#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct DummyParams : public core::IParameterParamsBase {
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    DummyParams() {
        params.push_back(&size);
    }
};
}
