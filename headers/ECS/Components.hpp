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
            RETROGRADE = -1
        };

        float mass = 9.f;
        float internalWatch = 0.f;

        bool canFall = true;

        void BodySpeed(Vector2& initialPos, Sense sense, Directions direction, float force) {
            const auto calc = (force / mass) * (int)sense;
            const auto calc_timer = calc * internalWatch * internalWatch / 2;

            switch (direction) {
            case HORIZONTAL:
                initialPos.x += calc_timer;
                break;
            case VERTICAL:
                initialPos.y -= calc_timer;
                break;
            case DIAGONAL:
                initialPos.x += calc_timer;
                initialPos.y -= calc_timer;
                break;
            }
        }
    };
}