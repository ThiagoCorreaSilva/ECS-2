#pragma once

#include <memory>
#include <iostream>

#include "../headers/ECS/Systems/Render.hpp"
#include "../build/Physcs.hpp"

enum class System
{
    RENDER,
    PHYSICS
};

class SystemsManager
{
private:
    std::unique_ptr<Render> render;
    std::unique_ptr<Physcs> physis;

public:
    SystemsManager()
    {
        render = std::make_unique<Render>();
        physis = std::make_unique<Physcs>();
    }

    void UpdateSystem(const System& system)
    {
       switch (system)
        {
            case System::RENDER:
                render->RenderEntities();
            break;

            case System::PHYSICS:
                physis->Gravity();
            break;
        }
    }
};