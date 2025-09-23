#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetCursorScreenPosParams {
    ParameterBase<const ImVec2&> pos = ParameterBase<const ImVec2&>("pos", ParameterType::INPUT);

    SetCursorScreenPosParams() = default;
};
