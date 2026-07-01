#pragma once

#include <optional>
#include <memory>

#include "EntityManager.hpp"
#include "ComponentsManager.hpp"

class ECS
{
private:
    static std::unique_ptr<EntityManager> entitiesManager;
    static std::unique_ptr<ComponentsManager> componentsManager;

public:
    static std::optional<Entity> CreateEntity()
    {
        return entitiesManager->CreateEntity();
    }

    static void DeleteEntity(Entity& entity)
    {
        entitiesManager->DeleteEntity(entity);
    }

    template <typename T>
    static std::optional<std::reference_wrapper<T>> AddComponent(Entity& entity)
    {
        return componentsManager->AddComponent<T>(entity);
    } 

    template <typename T>
    static std::optional<std::reference_wrapper<T>> GetComponent(Entity& entity)
    {
        return componentsManager->GetComponent<T>(entity);
    }

    template <typename T>
    static std::optional<std::reference_wrapper<T>> GetOrAddComponent(Entity& entity)
    {
        auto component = GetComponent<T>(entity);
        if (component.has_value())
        {
            return component;
        }

        component = AddComponent<T>(entity);
        return component;
    }

    template <typename T>
    static bool RemoveComponent(Entity& entity)
    {   
        return componentsManager->RemoveComponent<T>(entity);
    }
};

std::unique_ptr<EntityManager> ECS::entitiesManager = std::make_unique<EntityManager>();
std::unique_ptr<ComponentsManager> ECS::componentsManager = std::make_unique<ComponentsManager>(); 