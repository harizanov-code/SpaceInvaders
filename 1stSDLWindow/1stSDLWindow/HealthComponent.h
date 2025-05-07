// HealthComponent.h
#pragma once
#include "ECS.h"

class HealthComponent : public Component {
public:
    int maxHealth = 100;
    int currentHealth = 100;

    HealthComponent(int max = 100) : maxHealth(max), currentHealth(max) {
    }

    float getHealthPercent() const {
        return static_cast<float>(currentHealth) / maxHealth;
    }
};
