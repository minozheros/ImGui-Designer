#pragma once
#include <string>
#include <any>
#include <type_traits>
#include "core/types/interfaces/IParameter.hpp"
#include "core/types/base/ParameterBase.hpp"
#include "core/types/enums/ParameterType.hpp"

template <typename T>
class Parameter : public IParameter, public IParameterBase
{
public:
    // Constructor for lvalue references and copyable types
    template <typename U = T, typename = std::enable_if_t<!std::is_rvalue_reference_v<U>>>
    Parameter(const std::string &name, U &&defaultValue, ParameterType type)
        : name_(name), value_(std::forward<U>(defaultValue)), type_(type) {}

    // Constructor for default-constructible types
    template <typename U = T, typename = std::enable_if_t<std::is_default_constructible_v<U>>>
    Parameter(const std::string &name, ParameterType type)
        : name_(name), value_(), type_(type) {}

    // IParameter interface
    void render() override
    {
        // Default implementation - can be specialized for specific types
        // This would typically render ImGui controls
    }

    std::any getValue() const override
    {
        return std::any(value_);
    }

    void setValue(const std::any &value) override
    {
        try
        {
            value_ = std::any_cast<T>(value);
        }
        catch (const std::bad_any_cast &)
        {
            // Handle type mismatch
        }
    }

    std::string getName() const override
    {
        return name_;
    }

    std::string getType() const override
    {
        // Return a string representation of the type
        if constexpr (std::is_same_v<T, bool>)
            return "bool";
        else if constexpr (std::is_same_v<T, int>)
            return "int";
        else if constexpr (std::is_same_v<T, float>)
            return "float";
        else if constexpr (std::is_same_v<T, double>)
            return "double";
        else if constexpr (std::is_same_v<T, std::string>)
            return "string";
        else
            return "unknown";
    }

    // IParameterBase interface
    ParameterType getParameterType() const override
    {
        return type_;
    }

    void *getValuePtr() override
    {
        if constexpr (std::is_pointer_v<T>)
        {
            return &value_;
        }
        else
        {
            return &value_;
        }
    }

    std::any &getValueRef() override
    {
        static std::any ref = std::any(value_);
        ref = std::any(value_);
        return ref;
    }

    // Access to the actual value
    T &get() { return value_; }
    const T &get() const { return value_; }

    void set(const T &value) { value_ = value; }
    void set(T &&value) { value_ = std::move(value); }

private:
    std::string name_;
    T value_;
    ParameterType type_;
};