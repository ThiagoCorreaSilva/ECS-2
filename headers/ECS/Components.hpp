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

    struct Body 
    {
        enum Directions {
            HORIZONTAL,
            VERTICAL,
            DIAGONAL
        };

        enum Sense {
            PROGRESSIVE = 1,
            REATARDED = -1
        };

        float mass = 9.f;

        void Force(Vector2& initialPos, float& mass, Sense sense, Directions direction, float aceleration) {
            auto calc = mass * (int)sense * aceleration;

            switch (direction) {
            case HORIZONTAL:
                initialPos.x += 2 / initialPos.x + calc;
                break;
            case VERTICAL:
                initialPos.y -= 2 / initialPos.y + calc;
                break;
            case DIAGONAL:
                initialPos.x += 2 / initialPos.x + calc;
                initialPos.y -= 2 / initialPos.y + calc;
                break;
            }
        }
    };
}