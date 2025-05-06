#pragma once

#include "ECS.h"

#include "SDL3/SDL.h"

class TransformComponent;

class SpriteComponent : public Component {
private:
    TransformComponent* transform = nullptr;
    SDL_Texture* texture = nullptr;
    SDL_FRect srcRect, destRect;

    const char* path = nullptr;

public:
    SpriteComponent();
    SpriteComponent(const char* path);
    ~SpriteComponent();

    void setText(const char* path);
    void init() override;
    void update() override;
    void draw() override;

    const char* getPath();
};
