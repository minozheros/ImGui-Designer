#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
namespace core
{
    // Abstract interface for positionable components
    struct Positionable
    {
        virtual void setPosition(float x, float y) = 0;
        virtual void setPosition(const ImVec2 &pos) = 0;
        virtual void getPosition(float &x, float &y) const = 0;
        virtual float getX() const = 0;
        virtual float getY() const = 0;
        virtual ImVec2 getPosition() const = 0;
        virtual ~Positionable() = default;
    };
}