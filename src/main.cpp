#include <raylib.h>

#include <iostream>
#include <cassert>

#include "../headers/ECS/ECS.hpp"
#include "../headers/ECS/Collision.hpp"
#include "../headers/GameUI.hpp"
#include "../headers/Mecanics/Shot.hpp"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr const char* TITLE = "ECS-2";

constexpr float FIXED_PHYSICS = 1.f / 60.f;
float accumulator = 0.f;

Rectangle ground {0, 700, 400, 400};

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    InitAudioDevice();

    auto entity = ECS::CreateEntity();
    auto entity2 = ECS::CreateEntity();
    auto entity3 = ECS::CreateEntity();

    auto render = ECS::GetComponent<Components::Render>(entity.value());
    render.value().get().color = RED;

    auto component = ECS::GetComponent<Components::Transform>(entity.value());
    component.value().get().position.x = 200;

    auto ground_transform = ECS::GetComponent<Components::Transform>(entity2.value());
    ground_transform.value().get().position.x = ground.x;
    ground_transform.value().get().position.y = ground.y;
    ground_transform.value().get().size = ground.width;

    auto component2 = ECS::GetComponent<Components::Transform>(entity3.value());
    component2.value().get().position.x = 500;

    auto body = ECS::AddComponent<Components::Body>(entity.value());
    auto body2 = ECS::AddComponent<Components::Body>(entity3.value());

    float timer = 1.0f;
    
    void HorizontalMove(std::optional<std::reference_wrapper<Components::Body>>&compBody, std::optional<std::reference_wrapper<Components::Transform>>&compTrans, Components::Body::Sense sense);

    GameUI::Setup();
    while (!WindowShouldClose())
    {
        accumulator += GetFrameTime();
        if (accumulator >= FIXED_PHYSICS)
        {
            accumulator = 0.f;
            ECS::UpdateSystem(System::PHYSICS);
        }
        
        auto compTrans = Utility::FindComponent<Components::Transform>(entity.value());
        auto compBody = Utility::FindComponent<Components::Body>(entity.value());
        
        if (!compTrans) { 
            return 1; 
        }
        
        Rectangle actual = { 
            compTrans.value().get().position.x,
            compTrans.value().get().position.y,
            compTrans.value().get().size,
            compTrans.value().get().size
        };

        Shot myShot;
        
        if (IsKeyDown(KEY_D)) {
            HorizontalMove(compBody, compTrans, Components::Body::Sense::PROGRESSIVE);
        }
        else if (IsKeyDown(KEY_A)) {
            HorizontalMove(compBody, compTrans, Components::Body::Sense::RETROGRADE);
        }
        
        body.value().get().canFall = !IsEnter(actual, ground);
        
        ClearBackground(WHITE);
        BeginDrawing();
        myShot.DoShot(compTrans.value().get().position);
        
        ECS::UpdateSystem(System::RENDER);
        GameUI::Update();

        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void HorizontalMove(std::optional<std::reference_wrapper<Components::Body>>& compBody, std::optional<std::reference_wrapper<Components::Transform>>& compTrans, Components::Body::Sense sense)
{
    compBody.value().get().internalWatch = (compBody.value().get().canFall) ? .75f : 1.0f;
    compBody.value().get().BodySpeed(compTrans.value().get().position, sense, Components::Body::Directions::HORIZONTAL, 2.0f);
}