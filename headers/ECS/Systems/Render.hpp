#pragma once

#include <raylib.h>

#include <ranges>
#include <iostream>

#include "../headers/ECS/Components.hpp"
#include "../headers/Misc/Utility.hpp"

class Render
{
public:
    void RenderEntities()
    {
        for (const auto& entity : std::views::keys(Storage::entitiesComponents))
        {
            auto render = Utility::FindComponent<Components::Render>(entity);            
            auto transform = Utility::FindComponent<Components::Transform>(entity);

            if (!render.has_value() || !transform.has_value())
            {
                continue;
            }

            Rectangle rect {transform->get().position.x, transform->get().position.y, transform->get().size, transform->get().size};
            DrawRectangleRec(rect, render->get().color);
        }
    };
};