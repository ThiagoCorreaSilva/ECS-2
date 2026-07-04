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
    auto entity2 = ECS::CreateEntity();

    auto render = ECS::GetComponent<Components::Render>(entity.value());
    render.value().get().color = GREEN;

    auto render2 = ECS::GetComponent<Components::Render>(entity2.value());
    render2.value().get().color = RED;

    auto component = ECS::GetComponent<Components::Transform>(entity2.value());
    component.value().get().position.x = 200;

    auto phsycs = ECS::AddComponent<Components::Body>(entity2.value());
    phsycs.value().get().mass = 0.05f;

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        ECS::UpdateSystem(System::RENDER);
        ECS::UpdateSystem(System::PHYSICS);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}