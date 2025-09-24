#pragma once

    // Abstract interface for drawable components
    struct IDrawable
    {
        virtual bool draw() = 0;
        virtual ~IDrawable() = default;
        virtual bool isDrawable() const = 0;
       
    };
