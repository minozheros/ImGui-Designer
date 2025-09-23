#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct InputTextWithHintParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> hint = ParameterBase<const char*>("hint", ParameterType::INPUT);
    ParameterBase<char*> buf = ParameterBase<char*>("buf", ParameterType::INPUT);
    ParameterBase<size_t> buf_size = ParameterBase<size_t>("buf_size", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextCallback> callback = ParameterBase<ImGuiInputTextCallback>("callback", ParameterType::INPUT);
    ParameterBase<void*> user_data = ParameterBase<void*>("user_data", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    std::vector<core::IParameterBase*> params;
    InputTextWithHintParams() {
        params.push_back(&label);
        params.push_back(&hint);
        params.push_back(&buf);
        params.push_back(&buf_size);
        params.push_back(&flags);
        params.push_back(&callback);
        params.push_back(&user_data);
        params.push_back(&return_value);
    }
};
}
