#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetNextFrameWantCaptureMouseParams {
    ParameterBase<bool> want_capture_mouse = ParameterBase<bool>("want_capture_mouse", ParameterType::INPUT);

    SetNextFrameWantCaptureMouseParams() = default;
};
