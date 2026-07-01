#include <raylib.h>
#include <iostream>
#include <cassert>

#include "ECS.hpp"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;
constexpr const char* TITLE = "ECS-2";

void Tests();
void EntityTest();
void ComponentsTest();

int main()
{
    InitWindow(WIDTH, HEIGHT, TITLE);
    InitAudioDevice();

    Tests();

    while (!WindowShouldClose())
    {
        ClearBackground(WHITE);
        BeginDrawing();

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
}

void Tests()
{
    std::cout << "\n-----------------------\n";
    std::cout << "TESTING ENTITY AND COMPONENTS MANAGER\n";

    EntityTest();
    ComponentsTest();

    std::cout << "\n-----------------------\n";
    std::cout << "ALL TESTS FINISHED\n";
    std::cout << "-----------------------\n\n";
}

void EntityTest()
{
    std::cout << "\n------------------------\n";
    std::cout << "ENTITY MANAGER\n";
    std::cout << "------------------------\n";

    auto entity = ECS::CreateEntity();

    assert(entity.has_value() && "Entity not delivered");
    if (entity.has_value())
    {
        ECS::DeleteEntity(entity.value());
    }
}

void ComponentsTest()
{
    std::cout << "\n------------------------\n";
    std::cout << "COMPONENT MANAGER\n";
    std::cout << "------------------------\n";

    auto entity = ECS::CreateEntity().value();
    auto add = ECS::AddComponent<Components::Transform>(entity);

    assert(add.has_value() && "Component not delivered");
    if (add.has_value())
    {
        std::cout << "Component added\n";
    }

    auto get = ECS::GetComponent<Components::Transform>(entity);
    if (get.has_value())
    {
        int newValue = 10;

        std::cout << "Component getted\n";
        std::cout << "Position.x new value is " << newValue << '\n';

        get.value().get().position.x = newValue;
    }

    auto get2 = ECS::GetComponent<Components::Transform>(entity);

    assert(get2.has_value() && "Component not delivered");
    if (get2.has_value())
    {
        assert(get2.value().get().position.x == 10 && "Unexpected value");
    }

    ECS::RemoveComponent<Components::Transform>(entity);
}