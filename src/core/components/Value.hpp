#pragma once
#include <stdexcept>
#include <functional>
{
    // Templated Value component with min, max, default, overflow/underflow detection

    template <typename T>
    struct Value
    {
        using Handler = std::function<T(T)>;

        T value;

        T minValue;
        T maxValue;
        T defaultValue;

        Handler onOverflow = nullptr;
        Handler onUnderflow = nullptr;

        Value() = default;
        
        
        Value(T minV, T maxV , T defV,
              Handler overflowHandler = nullptr,
              Handler underflowHandler = nullptr)
            : value(defV), minValue(minV), maxValue(maxV), defaultValue(defV)
        {
            onOverflow = overflowHandler ? overflowHandler : [this](T)
            { return maxValue; };
            onUnderflow = underflowHandler ? underflowHandler : [this](T)
            { return minValue; };
        }

        void set(T v)
        {
            if (v < minValue)
            {
                value = onUnderflow(v);
            }
            else if (v > maxValue)
            {
                value = onOverflow(v);
            }
            else
            {
                value = v;
            }
        }

        T get() const { return value; }

        void reset() { value = defaultValue; }
    };
}