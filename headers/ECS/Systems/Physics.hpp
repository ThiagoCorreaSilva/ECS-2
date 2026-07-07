#pragma once

#include "raylib.h"

#include <algorithm> // Add this for std::transform if needed
#include <vector>    // Add this for std::vector if needed

#include "../headers/ECS/Components.hpp"
#include "../headers/Misc/Utility.hpp"

class Physcs {
private:
    const float force = 50.f;
    float timer = 0.f;
public:
    void Gravity() {
        // Fix: Replace std::views::keys with manual iteration over the map
        for (const auto& pair : Storage::entitiesComponents) {
            const auto& entity = pair.first;
            auto theBody = Utility::FindComponent<Components::Body>(entity);
            auto theTransform = Utility::FindComponent<Components::Transform>(entity);

            if (!theBody.has_value() || !theTransform.has_value()) {
                continue;
            }

            if (theBody->get().canFall) {
                theBody->get().internalWatch += 0.01f;
            } else {
                theBody->get().internalWatch = 0.f;
            }
            theBody->get().BodySpeed(theTransform->get().position, Components::Body::RETROGRADE, Components::Body::VERTICAL, force);
        }
    }
};