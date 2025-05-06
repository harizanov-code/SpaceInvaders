#pragma once

#include "ECS.h"

#include <vector>
#include <chrono>
#include <random>

class ColliderComponent;

class EnemySpawner {
private:
    Manager& manager;
    std::vector<Entity*> enemies;
    int maxEnemies = 9;          
    int maxEnemyBullets = 5;    
    float enemyShootCooldown = 1.0f; 
    float lastEnemyShootTime = 0.0f;
    std::mt19937 rng;             

    // Enemy formation variables
    int rows = 3;
    int columns = 3;
    float xSpacing = 100.0f;
    float ySpacing = 80.0f;
    float xOffset = 200.0f;       
    float yOffset = 100.0f; 
    
    

    // Movement pattern variables
    float moveSpeed = 0.5f;
    float moveDistance = 20.0f;
    bool movingRight = true;
    float dropDistance = 30.0f;

public:
    static float yOffsetS;
    EnemySpawner(Manager& mManager);
    ~EnemySpawner();

    void refreshEnemies();
    void spawnEnemyFormation();
    void update(float dt);
    void updateEnemyMovement(float dt);
    void tryEnemyShoot(float dt);
    int countActiveBullets();
    Entity* getRandomEnemy();
};