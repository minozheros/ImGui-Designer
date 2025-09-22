#pragma once
#include "core/interfaces/sizeable.hpp"
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui.h>
namespace core
{
    // Default implementation of Sizeable with storage
    class SizeableBase : public Sizeable
    {
    public:
        SizeableBase(float w = 0.0f, float h = 0.0f) : width(w), height(h) {}

        void setSize(const ImVec2 &size) override
        {
            width = size.x;
            height = size.y;
        }
        void setSize(float w, float h) override
        {
            width = w;
            height = h;
        }

        float getWidth() const override { return width; }
        float getHeight() const override { return height; }
        float getMinX(ImVec2 pos) const override { return pos.x; }
        float getMinY(ImVec2 pos) const override { return pos.y; }
        float getMaxX(ImVec2 pos) const override { return pos.x + width; }
        float getMaxY(ImVec2 pos) const override { return pos.y + height; }
        ImVec2 getMinPoint(ImVec2 pos) const override { return ImVec2(pos.x, pos.y); }
        ImVec2 getMaxPoint(ImVec2 pos) const override { return ImVec2(pos.x + width, pos.y + height); }
        ImVec2 getSize() const override { return ImVec2(width, height); }

    protected:
        float width;
        float height;
    };
}