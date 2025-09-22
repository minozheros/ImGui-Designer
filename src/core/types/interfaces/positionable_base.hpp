#pragma once
#include "core/interfaces/positionable.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
namespace core
{
    // Default implementation of Positionable with storage
    class PositionableBase : public Positionable
    {
    public:
        PositionableBase(float x_ = 0.0f, float y_ = 0.0f) : x(x_), y(y_) {}

        void setPosition(float x_, float y_) override
        {
            x = x_;
            y = y_;
        }
        void setPosition(const ImVec2 &pos) override
        {
            x = pos.x;
            y = pos.y;
        }
        void getPosition(float &x_, float &y_) const override
        {
            x_ = x;
            y_ = y;
        }
        float getX() const override { return x; }
        float getY() const override { return y; }
        ImVec2 getPosition() const override { return ImVec2(x, y); }

    protected:
        float x;
        float y;
    };
}