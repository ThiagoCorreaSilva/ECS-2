#pragma once

#include <memory>
#include <iostream>

#include "../headers/ECS/Systems/Render.hpp"

enum class System
{
    RENDER,
    PHYSICS
};

class SystemsManager
{
private:
    std::unique_ptr<Render> render;

public:
    SystemsManager()
    {
        render = std::make_unique<Render>();
    }

    void UpdateSystem(const System& system)
    {
       switch (system)
        {
            case System::RENDER:
                render->RenderEntities();
            break;

            case System::PHYSICS:
                std::cout << "Todo\n";
            break;
        }
    }
};