#pragma once
#include <imgui.h>
#include <core/types/base/parameter_base.hpp>

struct DummyParams {
    ParameterBase<const ImVec2&> size = ParameterBase<const ImVec2&>("size", ParameterType::INPUT);

    DummyParams() = default;
};
