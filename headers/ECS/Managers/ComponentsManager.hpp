#pragma once

#include <iostream>
#include <optional>
#include <algorithm>

#include "../headers/ECS/Components.hpp"
#include "../headers/Misc/Utility.hpp"

class ComponentsManager
{

private:
    template <typename T>
    std::optional<std::reference_wrapper<T>> TryAddComponent(unsigned short& entity)
    {
        Storage::entitiesComponents.at(entity).emplace_back(T{});
        if (auto ptr = std::any_cast<T>(&Storage::entitiesComponents.at(entity).back()))
        {
            return std::ref(*ptr);
        }
        else
        {
            return std::nullopt;
        }
    };

public:
    template <typename T>
    std::optional<std::reference_wrapper<T>> AddComponent(unsigned short& entity)
    {
        if (Storage::entitiesComponents.empty() || !Storage::entitiesComponents.contains(entity))
        {
            Storage::entitiesComponents.emplace(entity, std::vector<std::any>{});

            return TryAddComponent<T>(entity); 
        }

        auto result = Utility::FindComponent<T>(entity);
        if (!result.has_value())
        {
            std::cout << "Adding component " << typeid(T).name() << " to entity " << entity << '\n';
            return TryAddComponent<T>(entity);
        }

        std::cerr << "Entity " << entity << " already have component " << typeid(T).name() << '\n';
        return std::nullopt;
    }

    template <typename T>
    std::optional<std::reference_wrapper<T>> GetComponent(unsigned short& entity)
    {
        auto container = Storage::entitiesComponents;
        if (!container.contains(entity) || container.empty())
        {
            std::cerr << "Can't find entity " << entity << '\n';
            return std::nullopt;
        }

        return Utility::FindComponent<T>(entity);
    }

    template <typename T>
    bool RemoveComponent(unsigned short& entity)
    {
        if (Storage::entitiesComponents.empty() || !Storage::entitiesComponents.contains(entity))
        {
            std::cerr << "Empty entities_components container or can't find entity " << entity << '\n';
            return false;
        }

        auto& container = Storage::entitiesComponents.at(entity);
        auto it = std::find_if(container.begin(), container.end(), [](const auto& component){
            return component.type() == typeid(T);
        });

        if (it == container.end())
        {
            std::cerr << "Can't find component " << typeid(T).name() << " from entity " << entity << '\n';
            return false;
        }

        container.erase(it);
        std::cout << "Component " << typeid(T).name() << " removed from entity " << entity << '\n';

        return true;
    }

    template <typename T>
    bool HaveComponent(unsigned short& entity)
    {
        auto& container = Storage::entitiesComponents;
        if (!container.contains(entity) || container.empty())
        {
            std::cerr << "Can't check if entity " << entity << " have component " << typeid(T).name()
                      << " because container entities_components is empty or can't find the entity\n";

            return false;
        }

        auto it = std::find_if(container.at(entity).begin(), container.at(entity).end(), [](const auto& component){
            return component.type() == typeid(T);
        });

        if (it == container.at(entity).end())
        {
            return false;
        }

        return true;
    }
};