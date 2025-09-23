#pragma once
#include <imgui.h>
#include <vector>
#include <core/types/base/parameter_base.hpp>

namespace core
{
struct EndFrameParams {
    // No parameters


    std::vector<core::IParameterBase*> params;
    EndFrameParams() {
    }
};
}
