#pragma once

#include <memory>
#include <iostream>

#include "../headers/ECS/Systems/Render.hpp"
#include "../headers/ECS/Systems/Physics.hpp"

enum class System
{
    RENDER,
    PHYSICS
};

class SystemsManager
{
private:
    std::unique_ptr<Render> render;
    std::unique_ptr<Physcs> physcs;

public:
    SystemsManager()
    {
        render = std::make_unique<Render>();
        physcs = std::make_unique<Physcs>();
    }

    void UpdateSystem(const System& system)
    {
       switch (system)
        {
            case System::RENDER:
                render->RenderEntities();
            break;

            case System::PHYSICS:
                physcs->Gravity();
            break;
        }
    }
};