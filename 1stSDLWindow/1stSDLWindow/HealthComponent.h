// HealthComponent.h
#pragma once
#include "ECS.h"


class HealthComponent : public Component {
public:
    int maxHealth;
    int currentHealth;
    bool invulnerable = false;
    float invulnerabilityTime = 0.5f; // Seconds of invulnerability after damage
    float invulnerabilityTimer = 0.0f;

    HealthComponent(int max = 100);

    void init() override;
    void update() override;

    float getHealthPercent() const;
    bool takeDamage(int amount);
    void heal(int amount);
    bool isAlive() const;
};