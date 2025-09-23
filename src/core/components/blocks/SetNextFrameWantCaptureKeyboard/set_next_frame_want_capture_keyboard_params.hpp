#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextFrameWantCaptureKeyboardParams {
    ParameterBase<bool> want_capture_keyboard = ParameterBase<bool>("want_capture_keyboard", ParameterType::INPUT);

    SetNextFrameWantCaptureKeyboardParams() = default;
};
