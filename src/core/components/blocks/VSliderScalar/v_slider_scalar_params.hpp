#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct VSliderScalarParams : public core::IParameterParamsBase {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);
    ParameterBase<ImGuiDataType> data_type = ParameterBase<ImGuiDataType>("data_type", ParameterType::INPUT);
    ParameterBase<void*> p_data = ParameterBase<void*>("p_data", ParameterType::OUTPUT);
    ParameterBase<const void*> p_min = ParameterBase<const void*>("p_min", ParameterType::OUTPUT);
    ParameterBase<const void*> p_max = ParameterBase<const void*>("p_max", ParameterType::OUTPUT);
    ParameterBase<const char*> format = ParameterBase<const char*>("format", ParameterType::INPUT);
    ParameterBase<ImGuiSliderFlags> flags = ParameterBase<ImGuiSliderFlags>("flags", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    VSliderScalarParams() {
        params.push_back(&label);
        params.push_back(&size);
        params.push_back(&data_type);
        params.push_back(&p_data);
        params.push_back(&p_min);
        params.push_back(&p_max);
        params.push_back(&format);
        params.push_back(&flags);
        params.push_back(&return_value);
    }
};
}
