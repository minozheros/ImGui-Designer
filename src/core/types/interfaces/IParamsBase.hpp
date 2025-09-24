#pragma once
#include <vector>
#include "IParameter.hpp"

class IParamsBase
{
public:
    virtual ~IParamsBase() = default;
    virtual const std::vector<IParameter *> &getParameters() const = 0;
};
