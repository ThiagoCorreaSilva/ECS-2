#include <raylib.h>
#include <iostream>
#include <cassert>

#include "../headers/ECS/ECS.hpp"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr const char* TITLE = "ECS-2";

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    InitAudioDevice();

    auto entity = ECS::CreateEntity();

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        ECS::UpdateSystem(System::RENDER);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}