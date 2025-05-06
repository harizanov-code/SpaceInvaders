// EnemySpawner.h
#pragma once

#include "ECS.h"
#include <vector>
#include <random>

class EnemySpawner {
private:
    Manager& manager;
    std::vector<Entity*> enemies;

    // Formation configuration
    int rows = 3;
    int columns = 3;
    float xSpacing = 100.0f;
    float ySpacing = 80.0f;
    float xOffset = 200.0f;
    float yOffset = 100.0f;

    // Movement pattern variables
    float moveSpeed = 100.0f; // Units per second (adjusted for deltaTime)
    bool movingRight = true;
    float dropDistance = 30.0f;

    std::mt19937 rng; // Random number generator for enemy variations

public:
    static float yOffsetS;

    EnemySpawner(Manager& mManager);
    ~EnemySpawner();

    void spawnEnemyFormation();
    void update();
    void updateEnemyMovement();

    // This method would check if we need to spawn a new wave
    bool allEnemiesDestroyed() const {
        return enemies.empty();
    }

    // Remove inactive enemies from tracking
    void cleanupInactiveEnemies();
};