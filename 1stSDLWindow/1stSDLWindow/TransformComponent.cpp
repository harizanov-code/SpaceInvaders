#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "Game.h"
#include "EnemySpawner.h"
#include <iostream>

TransformComponent::TransformComponent() {
    position.Zero();
}

TransformComponent::TransformComponent(int scale) : scale(scale) {
    position.Zero();
}

TransformComponent::TransformComponent(float x, float y) {
    position.x = x;
    position.y = y;
}

TransformComponent::TransformComponent(float x, float y, float h, float w, int scale)
    : height(h), width(w), scale(scale) {
    position.x = x;
    position.y = y;
}

TransformComponent::TransformComponent(float x, float y, float h, float w, int scale, float xMax, float yMax)
    : height(h), width(w), scale(scale), xMax(xMax), yMax(yMax) {
    position.x = x;
    position.y = y;
}

void TransformComponent::init() {
    velocity.Zero();
}

void TransformComponent::resetWithOffset(float yOffset) {
    this->position.ResetWithOffset(yOffset);
}

void TransformComponent::update() {
    previousPosition = position;

    position.x += velocity.x;
    position.y += velocity.y;

    if (position.y < 0 || position.y > yMax || position.x < 0 || position.x >(xMax )) {
        if (entity->hasComponent<ColliderComponent>()) {
            auto& collider = entity->getComponent<ColliderComponent>();
            if (collider.tag == "bullet" || collider.tag == "enemyBullet" || collider.tag ==  "itemObject") {
                std::cout << "Went off the screen" << std::endl;
             
                active = false;
                entity->destroy();
            }
            else {
                //resetWithOffset(EnemySpawner::yOffsetS);
            }
        }
    }
}
