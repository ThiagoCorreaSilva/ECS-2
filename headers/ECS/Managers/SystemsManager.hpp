#pragma once

#include <any>
#include <span>
#include <vector>
#include <iostream>
#include <unordered_map>

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