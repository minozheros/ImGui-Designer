#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct SetCursorPosParams {
    ParameterBase<const ImVec2&> local_pos = ParameterBase<const ImVec2&>("local_pos", ParameterType::INPUT);

    SetCursorPosParams() = default;
};
