#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextFrameWantCaptureMouseParams : public core::IParameterParamsBase {
    ParameterBase<bool> want_capture_mouse = ParameterBase<bool>("want_capture_mouse", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextFrameWantCaptureMouseParams() {
        params.push_back(&want_capture_mouse);
    }
};
}
