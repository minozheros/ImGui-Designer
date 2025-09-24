#pragma once
namespace core
{
    // Abstract interface for drawable components
    struct Drawable
    {
        virtual bool draw() = 0;
        virtual ~Drawable() = default;
    };
}