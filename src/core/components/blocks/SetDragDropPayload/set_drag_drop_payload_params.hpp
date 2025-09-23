#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetDragDropPayloadParams : public core::IParameterParamsBase {
    ParameterBase<const char*> type = ParameterBase<const char*>("type", ParameterType::INPUT);
    ParameterBase<const void*> data = ParameterBase<const void*>("data", ParameterType::INPUT);
    ParameterBase<size_t> sz = ParameterBase<size_t>("sz", ParameterType::INPUT);
    ParameterBase<ImGuiCond> cond = ParameterBase<ImGuiCond>("cond", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    SetDragDropPayloadParams() {
        params.push_back(&type);
        params.push_back(&data);
        params.push_back(&sz);
        params.push_back(&cond);
        params.push_back(&return_value);
    }
};
}
