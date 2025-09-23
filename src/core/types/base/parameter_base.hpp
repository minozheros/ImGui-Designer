#pragma once
#include <string>
#include "core/components/value.hpp"
#include "core/types/enums/parameter_type.hpp"

namespace core
{
    struct IParameterBase
    {
        virtual ~IParameterBase() = default;
        virtual std::string getName() const = 0;
        virtual ParameterType getType() const = 0;
    };

    template <typename T>
    struct ParameterBase : public IParameterBase
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

        ~ParameterBase() override = default;

        std::string getName() const override { return name; }
        Value<T> getValue() const { return value; }
        ParameterType getType() const override { return type; }
    };
}