#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>
#include <core/types/interfaces/IParameterParamsBase.hpp>

namespace core {
struct SetNextFrameWantCaptureKeyboardParams : public core::IParameterParamsBase {
    ParameterBase<bool> want_capture_keyboard = ParameterBase<bool>("want_capture_keyboard", ParameterType::INPUT);

    std::vector<core::IParameterBase*> params;
    SetNextFrameWantCaptureKeyboardParams() {
        params.push_back(&want_capture_keyboard);
    }
};
}
