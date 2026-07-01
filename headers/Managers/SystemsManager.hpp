#pragma once

#include <iostream>

enum class System
{
    RENDER,
    PHYSICS
};

class SystemsManager
{
public:
    void UpdateSystem(const System& system)
    {
       switch (system)
        {
            case System::RENDER:
            break;

            case System::PHYSICS:
                std::cout << "Todo\n";
            break;
        }
    }
};