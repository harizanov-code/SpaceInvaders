// ShootingComponent.cpp
#include "ShootingComponent.h"
#include "Game.h"
#include "TransformComponent.h"
#include "ECS.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "DamageComponent.h" // Add this include
#include "ENUMS.h"

ShootingComponent::ShootingComponent(float cooldown, std::string bulletSprite,
    std::string bulletTag, bool shootDown)
    : cooldown(cooldown), bulletSprite(bulletSprite),
    bulletTag(bulletTag), shootDown(shootDown) {
    // Add randomness to initial timer
    timer = static_cast<float>(rand()) / RAND_MAX * cooldown;
}

void ShootingComponent::init() {
    if (!entity->hasComponent<TransformComponent>()) {
        entity->addComponent<TransformComponent>();
    }
    transform = &entity->getComponent<TransformComponent>();
}

void ShootingComponent::update() {
    timer += Game::deltaTime;  // Assuming Game has a deltaTime property
    // Try to shoot when cooldown is reached
    if (timer >= cooldown) {
        shoot();
        timer = 0;
    }
}

void ShootingComponent::shoot() {
    int existingBullets = 0;

    if (entity->hasComponent<ColliderComponent>() &&
        entity->getComponent<ColliderComponent>().tag == bulletTag &&
        entity->isActive()) {
        existingBullets++;
    }

    if (existingBullets >= 5) return;

    // Create bullet
    auto& bullet(entity->getManager().addEntity());

    // Position at the center-bottom of the entity
    float bulletX = transform->position.x + transform->width / 2;
    float bulletY = shootDown ?
        transform->position.y + transform->height :
        transform->position.y;

    bullet.addComponent<TransformComponent>(bulletX, bulletY);
    bullet.addComponent<SpriteComponent>(bulletSprite.c_str());
    bullet.addComponent<ColliderComponent>(bulletTag.c_str());
    bullet.addComponent<DamageComponent>(bulletDamage); 
    bullet.addGroup(groupProjectile);

 
    auto& bulletTransform = bullet.getComponent<TransformComponent>();
    bulletTransform.velocity.y = shootDown ? bulletSpeed : -bulletSpeed;
}