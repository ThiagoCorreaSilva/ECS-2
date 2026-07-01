#pragma once

#include <raylib.h>

namespace Components
{
    struct Transform
    {
        Vector2 position = Vector2(0, 0);
        float size = 10.f;
        float rotation = 0.f;    
    };

    struct Render
    {
        Color color = PURPLE;
    };
}