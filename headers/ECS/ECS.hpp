#pragma once

#include <memory>
#include <optional>

#include "../headers/ECS/Managers/EntityManager.hpp"
#include "../headers/ECS/Managers/ComponentsManager.hpp"
#include "../headers/ECS/Managers/SystemsManager.hpp"

class ECS
{
private:
    static std::unique_ptr<EntityManager> entitiesManager;
    static std::unique_ptr<ComponentsManager> componentsManager;
    static std::unique_ptr<SystemsManager> systemsManager;

private:
    static bool AddDefaultComponents(Entity& entity)
    {
        auto transform = componentsManager->AddComponent<Components::Transform>(entity);
        auto render = componentsManager->AddComponent<Components::Render>(entity);

        if (!transform.has_value() || !render.has_value())
        {
            return false;
        }

        return true;
    }

public:
    static std::optional<Entity> CreateEntity()
    {
        auto entity = entitiesManager->CreateEntity();
        if (!entity.has_value())
        {
            return std::nullopt;
        }

        if (!AddDefaultComponents(entity.value()))
        {
            return std::nullopt;
        }

        return entity;
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

    static void UpdateSystem(const System& system)
    {
        systemsManager->UpdateSystem(system);
    }
};

std::unique_ptr<EntityManager> ECS::entitiesManager = std::make_unique<EntityManager>();
std::unique_ptr<ComponentsManager> ECS::componentsManager = std::make_unique<ComponentsManager>();
std::unique_ptr<SystemsManager> ECS::systemsManager = std::make_unique<SystemsManager>();