#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct SetNextFrameWantCaptureMouseParams {
    ParameterBase<bool> want_capture_mouse = ParameterBase<bool>("want_capture_mouse", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextFrameWantCaptureMouseParams() {
        params.push_back(&want_capture_mouse);
    }
};
}
