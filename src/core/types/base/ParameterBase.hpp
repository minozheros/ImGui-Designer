#pragma once
#include <string>
#include "core/types/enums/ParameterType.hpp"

struct IParameterBase
{
    virtual ~IParameterBase() = default;
    virtual std::string getName() const = 0;
    virtual ParameterType getParameterType() const = 0;
};
