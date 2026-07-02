#pragma once

#include <raylib.h>

#include <iostream>
#include <algorithm>

#include "../headers/ECS/Components.hpp"
#include "../headers/ECS/Storage.hpp"

class Render
{
public:
    void RenderEntities()
    {
        for (auto& [_, components] : Storage::entitiesComponents)
        {
            // NEED TO REFACTOR ALL THAT SHIT AND MAKE IT WORK
            auto it_render = std::find_if(components.begin(), components.end(), [](const auto& component){
                return component.type() == typeid(Components::Render); 
            });

            if (it_render == components.end())
            {
                continue;
            }

            auto it_transform = std::find_if(components.begin(), components.end(), [](const auto& component){
                return component.type() == typeid(Components::Transform); 
            });

            if (it_transform == components.end())
            {
                continue;
            }

            auto render = std::any_cast<Components::Render>(*it_render);
            auto transform = std::any_cast<Components::Transform>(*it_transform);

            Rectangle rect {transform.position.x, transform.position.y, transform.size, transform.size};
            DrawRectangleRec(rect, render.color);
        } 
    };
};