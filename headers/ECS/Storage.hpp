#pragma once

#include <any>
#include <vector>
#include <unordered_map>

class Storage
{
public:
    inline static std::unordered_map<unsigned short, std::vector<std::any>> entitiesComponents;
};