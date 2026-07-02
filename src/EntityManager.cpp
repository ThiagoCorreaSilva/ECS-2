#include "../headers/ECS/Managers/EntityManager.hpp"
#include <iostream>

EntityManager::EntityManager()
{
    m_entities.reserve(MAX_ENTITIES);

    for (Entity i = MAX_ENTITIES; i != 0; i--)
    {
        m_entities.push_back(i);
    }

    std::cout << "Entities pool initialized with: " << m_entities.size() << " entities\n";
}

std::optional<Entity> EntityManager::CreateEntity()
{
    if (m_entities.empty())
    {
        std::cerr << "Don't have any entities in pool\n";
        return std::nullopt;
    }

    Entity entity = m_entities.back();
    m_entities.pop_back();

    std::cout << "Entity " << entity << " created, entities in pool: " << m_entities.size() << '\n';

    return entity;
}

void EntityManager::DeleteEntity(Entity& entity)
{
    if (entity > MAX_ENTITIES)
    {
        std::cerr << "Invalid entity ID to delete";
        return;
    }

    if (m_entities.size() >= MAX_ENTITIES)
    {
        std::cerr << "Entities pool is full\n";
        return;
    }

    m_entities.push_back(entity);
    std::cout << "Entity " << entity << " deleted, entities in pool: " << m_entities.size() << '\n';
}