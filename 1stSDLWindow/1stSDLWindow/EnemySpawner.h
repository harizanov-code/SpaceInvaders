#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include <vector>
#include <chrono>
#include <random>

class EnemySpawner {
private:
    Manager& manager;
    std::vector<Entity*> enemies;
    int maxEnemies = 3;          // Maximum number of enemies on screen
    int maxEnemyBullets = 5;      // Maximum number of bullets all enemies can fire
    float enemyShootCooldown = 1.0f; // Time between enemy shots
    float lastEnemyShootTime = 0.0f;
    std::mt19937 rng;             // Random number generator

    // Enemy formation variables
    int rows = 1;
    int columns = 3;
    float xSpacing = 100.0f;
    float ySpacing = 80.0f;
    float xOffset = 200.0f;       // Starting X position
    float yOffset = 100.0f; 
    
    

    // Movement pattern variables
    float moveSpeed = 0.5f;
    float moveDistance = 20.0f;
    bool movingRight = true;
    float dropDistance = 30.0f;

public:
    EnemySpawner(Manager& mManager);
    ~EnemySpawner();

    void spawnEnemyFormation();
    void update(float dt);
    void updateEnemyMovement(float dt);
    void tryEnemyShoot(float dt);
    int countActiveBullets();
    Entity* getRandomEnemy();
};