#pragma once

#include <optional>
#include <algorithm>

#include "../headers/ECS/Storage.hpp"

class Utility
{
public:
    template <typename T>
    static std::optional<std::reference_wrapper<T>> GetComponent(const unsigned short& entity)
    {
        auto components = Storage::entitiesComponents.at(entity);

        auto it = std::find_if(components.begin(), components.end(), [](const auto& component){
            return component.type() == typeid(T);
        });

        if (it == components.end())
        {
            return std::nullopt;
        }

        if (auto render = std::any_cast<T>(&*it))
        {
            return std::ref(*render);
        }

        return std::nullopt;
    } 
};