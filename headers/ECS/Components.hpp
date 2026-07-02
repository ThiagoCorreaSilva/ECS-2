#pragma once

#include <raylib.h>

namespace Components
{
    struct Render
    {
        Color color = PURPLE;
    };

    struct Transform
    {
        Vector2 position = Vector2(500, 500);
        float size = 10.f;
        float rotation = 0.f;    
    };
}