// EnemySpawner.cpp
#include "EnemySpawner.h"
#include "Game.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "ShootingComponent.h"
#include "ENUMS.h"
#include <iostream>
#include "HealthComponent.h"
#include "EnemyFactory.h" // Add this include

float EnemySpawner::yOffsetS = 64.0f;

EnemySpawner::EnemySpawner(Manager& mManager)
    : manager(mManager), rng(std::random_device{}()) {
    // Initialize enemy configs
    EnemyFactory::initialize();
}

EnemySpawner::~EnemySpawner() {
}

void EnemySpawner::spawnEnemyFormation() {
    // Clear any existing enemies
    enemies.clear();

    // Create a grid of enemies
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            float xPos = xOffset + col * xSpacing;
            float yPos = yOffset + row * ySpacing;

            // Determine enemy type based on row
            EnemyType type;
            if (row == 0) {
                type = EnemyType::LARGE;
            }
            else if (row == 1) {
                type = EnemyType::MEDIUM;
            }
            else {
                type = EnemyType::SMALL;
            }

            // Create the enemy using factory
            auto& enemy = EnemyFactory::createEnemy(manager, type, xPos, yPos);
            enemies.push_back(&enemy);
        }
    }

    std::cout << "Spawned " << enemies.size() << " enemies" << std::endl;
}

// Rest of the implementation remains the same
void EnemySpawner::update() {
    // Update movement pattern
    cleanupInactiveEnemies();
    updateEnemyMovement();
}

void EnemySpawner::updateEnemyMovement() {
    bool shouldChangeDirection = false;

    // Check if any enemy would hit the edge of the screen
    for (auto* enemy : enemies) {
        if (!enemy->isActive()) continue;

        auto& pos = enemy->getComponent<TransformComponent>().position;

        if ((movingRight && pos.x > 924) || (!movingRight && pos.x < 50)) {
            shouldChangeDirection = true;
            break;
        }
    }

    // Move all enemies
    for (auto* enemy : enemies) {
        if (!enemy->isActive()) continue;

        auto& transform = enemy->getComponent<TransformComponent>();

        if (shouldChangeDirection) {
            // Change direction and move down
            movingRight = !movingRight;
            transform.position.y += dropDistance;
            transform.velocity * -1;
        }
    }
}

void EnemySpawner::cleanupInactiveEnemies() {
    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
            [](Entity* e) {
        if (e->isActive() == 1) {
            return false;
        }
        else {
            return true;
        }
    }),
        enemies.end()
    );
}