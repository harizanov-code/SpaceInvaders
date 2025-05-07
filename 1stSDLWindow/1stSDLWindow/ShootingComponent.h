
#pragma once
#include "ECS.h"

class TransformComponent;

class ShootingComponent : public Component {
private:
    TransformComponent* transform;
    float cooldown = 10.0f;             // Time between shots
    float timer = 0.0f;                // Current timer
    float bulletSpeed = 5.0f;          // Speed of bullets
    std::string bulletTag = "enemyBullet";  // Tag for collision detection
    std::string bulletSprite = "Pictures/Bullet_1_Enemy.png"; // Bullet sprite
    bool shootDown = true;             // Direction: down=true, up=false
    int bulletDamage = 10;             // Damage amount for bullets

public:
    ShootingComponent() = default;
    ShootingComponent(float cooldown, std::string bulletSprite,
        std::string bulletTag, bool shootDown = true);

    void init() override;
    void update() override;

    void setCooldown(float cd) {
        cooldown = cd;
    }
    void setBulletSpeed(float speed) {
        bulletSpeed = speed;
    }
    void setBulletSprite(const std::string& sprite) {
        bulletSprite = sprite;
    }
    void setBulletDamage(int damage) {
        bulletDamage = damage;
    }

    void shoot();  // Attempt to create a bullet
};