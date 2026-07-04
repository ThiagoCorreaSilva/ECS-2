#pragma once

#include <raylib.h>
#include <iostream>

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

        void BodySpeed(Vector2& initialPos, Sense sense, Directions direction, float aceleration) {
            const auto calc = mass * (int)sense * aceleration * aceleration;
           /* const int divisor = 200000;
            const Vector2 controllVec = { initialPos.x / divisor , initialPos.y / divisor };*/

            switch (direction) {
            case HORIZONTAL:
                initialPos.x += calc;
                std::cout << "POS X : " << initialPos.x << '\n';
                break;
            case VERTICAL:
                initialPos.y -= calc;
                break;
            case DIAGONAL:
                initialPos.x += calc;
                initialPos.y -= calc;
                break;
            }
        }
    };
}