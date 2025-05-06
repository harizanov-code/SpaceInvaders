#include "EnemySpawner.h"
#include <iostream>
#include "ENUMS.h"
EnemySpawner::EnemySpawner(Manager& mManager)
    : manager(mManager), rng(std::random_device{}()) {
}

EnemySpawner::~EnemySpawner() {
}

void EnemySpawner::spawnEnemyFormation() {
    // Clear any existing enemies
    enemies.clear();

    // Create a grid of enemies
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            auto& enemy = manager.addEntity();

            float xPos = xOffset + col * xSpacing;
            float yPos = yOffset + row * ySpacing;

            //1024 is the max X and max Y of the screen
            enemy.addComponent<TransformComponent>(xPos, yPos, 64, 64, 1, 1024, 1024);
            enemy.getComponent<TransformComponent>().velocity.x += 1;
            enemy.addComponent<SpriteComponent>("Pictures/Enemies/Enemy_Level1_Cloud.png");
            enemy.addComponent<ColliderComponent>("enemy");
            enemy.addGroup(groupEnemies);

            enemies.push_back(&enemy);
        }
    }

    std::cout << "Spawned " << enemies.size() << " enemies" << std::endl;
}

//void EnemySpawner::update(float dt) {
//    // Update the movement pattern
//    updateEnemyMovement(dt);
//
//    // Try to make an enemy shoot
//    tryEnemyShoot(dt);
//
//    // Check if all enemies are dead
//    if (enemies.empty()) {
//        spawnEnemyFormation();
//    }
//}

//void EnemySpawner::updateEnemyMovement(float dt) {
//    bool shouldChangeDirection = false;
//    float moveAmount = moveSpeed * dt;
//
//    // Check if any enemy would hit the edge of the screen
//    for (auto* enemy : enemies) {
//        if (!enemy->isActive()) continue;
//
//        auto& pos = enemy->getComponent<TransformComponent>().position;
//        if ((movingRight && pos.x > 900) || (!movingRight && pos.x < 100)) {
//            shouldChangeDirection = true;
//            break;
//        }
//    }
//
//    // Move all enemies
//    for (auto* enemy : enemies) {
//        if (!enemy->isActive()) continue;
//
//        auto& transform = enemy->getComponent<TransformComponent>();
//
//        if (shouldChangeDirection) {
//            // Change direction and move down
//            movingRight = !movingRight;
//            transform.position.y += dropDistance;
//        }
//        else {
//            // Move horizontally
//            transform.position.x += movingRight ? moveAmount : -moveAmount;
//        }
//    }
//
//    // Remove inactive enemies from our list
//    enemies.erase(
//        std::remove_if(enemies.begin(), enemies.end(),
//            [](Entity* e) { return !e->isActive(); }
//        ),
//        enemies.end()
//    );
//}

int EnemySpawner::countActiveBullets() {
    int count = 0;
    for (auto& entity : manager.entities) {
        if (entity->hasComponent<ColliderComponent>() &&
            entity->getComponent<ColliderComponent>().tag == "enemyBullet" &&
            entity->isActive()) {
            count++;
        }
    }
    return count;
}

Entity* EnemySpawner::getRandomEnemy() {
    if (enemies.empty()) return nullptr;

    std::uniform_int_distribution<int> dist(0, enemies.size() - 1);
    return enemies[dist(rng)];
}

void EnemySpawner::tryEnemyShoot(float dt) {
    // Check if enough time has passed and we have fewer than max bullets
    lastEnemyShootTime += dt;
    if (lastEnemyShootTime < enemyShootCooldown) return;

    // Reset timer but add some randomness
    std::uniform_real_distribution<float> cooldownVariation(0.0f, 1.0f);
    lastEnemyShootTime = -cooldownVariation(rng);

    // Don't shoot if we already have max bullets
    if (countActiveBullets() >= maxEnemyBullets) return;

    // Get a random enemy to shoot
    Entity* shooter = getRandomEnemy();
    if (!shooter) return;

    // Create a bullet
    auto& bullet = manager.addEntity();
    auto& shooterTransform = shooter->getComponent<TransformComponent>();

    // Position the bullet at the bottom of the enemy
    float bulletX = shooterTransform.position.x + shooterTransform.width / 2;
    float bulletY = shooterTransform.position.y + shooterTransform.height;

    bullet.addComponent<TransformComponent>(bulletX, bulletY);
    bullet.addComponent<SpriteComponent>("Pictures/Bullet_1_Enemy.png");
    bullet.addComponent<ColliderComponent>("enemyBullet");
    bullet.addGroup(groupProjectile);

    // Set bullet velocity downward
    auto& bulletTransform = bullet.getComponent<TransformComponent>();
    bulletTransform.velocity.y = 5; // Moving down
}