#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
namespace core
{
    // Abstract interface for sizeable components
    struct Sizeable
    {
        virtual void setSize(const ImVec2 &size) = 0;
        virtual void setSize(float width, float height) = 0;
        virtual float getWidth() const = 0;
        virtual float getHeight() const = 0;
        virtual ImVec2 getSize() const = 0;

        // Extra helpers for bounding box calculations
        virtual float getMinX(ImVec2 pos) const = 0;
        virtual float getMinY(ImVec2 pos) const = 0;
        virtual float getMaxX(ImVec2 pos) const = 0;
        virtual float getMaxY(ImVec2 pos) const = 0;
        virtual ImVec2 getMinPoint(ImVec2 pos) const = 0;
        virtual ImVec2 getMaxPoint(ImVec2 pos) const = 0;

        virtual ~Sizeable() = default;
    };
}