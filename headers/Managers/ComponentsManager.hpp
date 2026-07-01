#pragma 

#include <any>
#include <vector>
#include <iostream>
#include <optional>
#include <algorithm>
#include <unordered_map>

#include "../headers/Components.hpp"

class ComponentsManager
{
private:
    std::unordered_map<unsigned short, std::vector<std::any>> m_entitiesComponents;

public:
    template <typename T>
    std::optional<std::reference_wrapper<T>> AddComponent(unsigned short& entity)
    {
        if (m_entitiesComponents.empty() || !m_entitiesComponents.contains(entity))
        {
            m_entitiesComponents.emplace(entity, std::vector<std::any>{});
            m_entitiesComponents.at(entity).emplace_back(T{});

            if (auto ptr = std::any_cast<T>(&m_entitiesComponents.at(entity).back()))
            {
                return std::ref(*ptr);
            }
            else
            {
                return std::nullopt;
            }
        }

        for (const auto& component : m_entitiesComponents.at(entity))
        {
            if (component.type() == typeid(T))
            {
                std::cerr << "Entity " << entity << " already have component " << typeid(T).name() << '\n';
                return std::nullopt;
            }
        }
        
        return std::nullopt;
    }

    template <typename T>
    std::optional<std::reference_wrapper<T>> GetComponent(unsigned short& entity)
    {
        if (!m_entitiesComponents.contains(entity))
        {
            std::cerr << "Can't find entity " << entity << '\n';
            return std::nullopt;
        }

        for (auto& component : m_entitiesComponents.at(entity))
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
        if (m_entitiesComponents.empty() || !m_entitiesComponents.contains(entity))
        {
            std::cerr << "Empty entities_components container or can't find entity " << entity << '\n';
            return false;
        }

        auto& container = m_entitiesComponents.at(entity);
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
};