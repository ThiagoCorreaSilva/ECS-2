#pragma once

#include <raylib.h>

namespace Components
{
    struct Transform
    {
        Vector2 position;
        float size;
        float rotation;    
    };

    struct Style
    {
        Color color;
    };
}