#pragma once
#include "core/components/value.hpp"
#include "core/types/enums/parameter_type.hpp"
namespace core
{
    template <typename T>
    struct ParameterBase
    {
        std::string name;
        Value<T> value;
        ParameterType type;

        ParameterBase(const std::string &name, ParameterType type)
            : name(name), type(type)
        {
            value = Value<T>();
        }

        ParameterBase(const std::string &name, const Value<T> &value, ParameterType type)
            : name(name), value(value), type(type) {}

        virtual ~ParameterBase() = default;

        std::string getName() const { return name; }
        Value<T> getValue() const { return value; }
        ParameterType getType() const { return type; }
    };
}