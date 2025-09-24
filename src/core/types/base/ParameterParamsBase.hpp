#pragma once
#include <vector>
#include "core/types/base/ParameterBase.hpp"

class IParamsBase
{
public:
    virtual ~IParamsBase() = default;
    virtual const std::vector<IParameter *> &getParameters() const = 0;
};
