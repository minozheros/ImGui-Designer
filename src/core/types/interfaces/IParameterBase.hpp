#pragma once
#include <string>
#include "core/types/enums/parameter_type.hpp"

namespace core
{
    struct IParameterBase
    {
        virtual ~IParameterBase() = default;
        virtual std::string getName() const = 0;
        virtual ParameterType getType() const = 0;
    };
}
