#pragma once

#include <vector>
#include <optional>

using Entity = unsigned short int;
constexpr std::size_t MAX_ENTITIES = 100;

class EntityManager
{
private:
    std::vector<Entity> m_entities;

public:
    EntityManager();

    std::optional<Entity> CreateEntity();
    void DeleteEntity(Entity& entity);
};