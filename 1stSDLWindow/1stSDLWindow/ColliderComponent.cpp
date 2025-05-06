#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include <iostream>

ColliderComponent::ColliderComponent(std::string tag) {
    this->tag = tag;
}

void ColliderComponent::init() {
    if (!entity->hasComponent<TransformComponent>()) {
        entity->addComponent<TransformComponent>();
    }

    transform = &entity->getComponent<TransformComponent>();
    Game::colliders.emplace_back(this);  // No need for std::move on `this`
}

void ColliderComponent::update() {
    collider.x = transform->position.x;
    collider.y = transform->position.y;
    collider.w = transform->width * transform->scale;
    collider.h = transform->height * transform->scale;
}

std::string ColliderComponent::getTag() {
    return this->tag;
}
