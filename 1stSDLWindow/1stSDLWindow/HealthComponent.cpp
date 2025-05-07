// HealthComponent.cpp
#include "HealthComponent.h"
#include <iostream>
#include "Game.h"
HealthComponent::HealthComponent(int max) : maxHealth(max), currentHealth(max) {
}

void HealthComponent::init() {
    // Nothing to initialize
}

void HealthComponent::update() {
    // Update invulnerability timer
    if (invulnerable) {
        invulnerabilityTimer -= Game::deltaTime;
        if (invulnerabilityTimer <= 0) {
            invulnerable = false;
        }
    }
}

float HealthComponent::getHealthPercent() const {
    return static_cast<float>(currentHealth) / maxHealth;
}

bool HealthComponent::takeDamage(int amount) {
    if (invulnerable) return false;

    currentHealth -= amount;
    if (currentHealth <= 0) {
        currentHealth = 0;
        return true; // Entity should be destroyed
    }

    // Start invulnerability period
    invulnerable = true;
    invulnerabilityTimer = invulnerabilityTime;

    return false;
}

void HealthComponent::heal(int amount) {
    currentHealth += amount;
    if (currentHealth > maxHealth) {
        currentHealth = maxHealth;
    }
}

bool HealthComponent::isAlive() const {
    return currentHealth > 0;
}