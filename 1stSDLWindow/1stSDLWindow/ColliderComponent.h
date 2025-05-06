#pragma once

#include <string>
#include "SDL3/SDL.h"
#include "ECS.h"
class TransformComponent;

class ColliderComponent : public Component {
public:
    SDL_FRect collider;
    std::string tag;
    TransformComponent* transform = nullptr;

    ColliderComponent(std::string tag);

    void init() override;
    void update() override;

    std::string getTag();
};
