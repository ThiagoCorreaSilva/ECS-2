#pragma once

#include <iostream>
#include <optional>
#include <algorithm>

#include "../headers/ECS/Components.hpp"
#include "../headers/ECS/Storage.hpp"

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

        for (const auto& component : Storage::entitiesComponents.at(entity))
        {
            if (component.type() == typeid(T))
            {
                std::cerr << "Entity " << entity << " already have component " << typeid(T).name() << '\n';
                return std::nullopt;
            }

            return TryAddComponent<T>(entity);
        }
        
        return std::nullopt;
    }

    template <typename T>
    std::optional<std::reference_wrapper<T>> GetComponent(unsigned short& entity)
    {
        if (!Storage::entitiesComponents.contains(entity))
        {
            std::cerr << "Can't find entity " << entity << '\n';
            return std::nullopt;
        }

        for (auto& component : Storage::entitiesComponents.at(entity))
        {
            if (component.type() == typeid(T))
            {
                if (auto ptr = std::any_cast<T>(&component))
                {
                    return std::ref(*ptr);
                }
                else
                {
                    std::cerr << "Can't find component " << typeid(T).name() << " of entity " << entity << '\n';
                    return std::nullopt;
                }
            }
        }

        return std::nullopt;
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