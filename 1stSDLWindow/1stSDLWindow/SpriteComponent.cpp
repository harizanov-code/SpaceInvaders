#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "TextureManager.h"
#include <iostream>

SpriteComponent::SpriteComponent() = default;

SpriteComponent::SpriteComponent(const char* path) {
    this->path = path;
    setText(path);
}

SpriteComponent::~SpriteComponent() {
    if (texture) {
        SDL_DestroyTexture(texture);
    }
}

void SpriteComponent::setText(const char* path) {
    texture = TextureManager::LoadTexture(path);
}

void SpriteComponent::init() {
    transform = &entity->getComponent<TransformComponent>();

    srcRect.x = srcRect.y = 0;
    srcRect.w = transform->width;
    srcRect.h = transform->height;
}

void SpriteComponent::update() {
    destRect.x = transform->position.x;
    destRect.y = transform->position.y;
    destRect.w = transform->width * transform->scale;
    destRect.h = transform->height * transform->scale;
}

void SpriteComponent::draw() {
    TextureManager::Draw(texture, srcRect, destRect);
}

const char* SpriteComponent::getPath() {
    return path;
}
