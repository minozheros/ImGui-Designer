#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct InputTextWithHintParams {
    ParameterBase<const char*> label = ParameterBase<const char*>("label", ParameterType::INPUT);
    ParameterBase<const char*> hint = ParameterBase<const char*>("hint", ParameterType::INPUT);
    ParameterBase<char*> buf = ParameterBase<char*>("buf", ParameterType::INPUT);
    ParameterBase<size_t> buf_size = ParameterBase<size_t>("buf_size", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextFlags> flags = ParameterBase<ImGuiInputTextFlags>("flags", ParameterType::INPUT);
    ParameterBase<ImGuiInputTextCallback> callback = ParameterBase<ImGuiInputTextCallback>("callback", ParameterType::INPUT);
    ParameterBase<void*> user_data = ParameterBase<void*>("user_data", ParameterType::INPUT);
    ParameterBase<bool> return_value = ParameterBase<bool>("return_value", ParameterType::RETURN);

    InputTextWithHintParams() = default;
};
