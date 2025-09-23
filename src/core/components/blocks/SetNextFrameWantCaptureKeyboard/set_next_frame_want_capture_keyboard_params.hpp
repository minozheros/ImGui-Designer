#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextFrameWantCaptureKeyboardParams {
    ParameterBase<bool> want_capture_keyboard = ParameterBase<bool>("want_capture_keyboard", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextFrameWantCaptureKeyboardParams() {
        params.push_back(&want_capture_keyboard);
    }
};
}
