// EnemySpawner.cpp
#include "EnemySpawner.h"
#include "Game.h"
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "SpriteComponent.h"
#include "ShootingComponent.h" // New component
#include "ENUMS.h"
#include <iostream>

float EnemySpawner::yOffsetS = 64.0f;

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

			// Position and appearance
			enemy.addComponent<TransformComponent>(xPos, yPos, 64, 64, 1, 1024, 1024);
			enemy.getComponent<TransformComponent>().velocity.x = 1.0f; // Adjusted for deltaTime
			enemy.addComponent<SpriteComponent>("Pictures/Enemies/Enemy_Level1_Cloud.png");
			enemy.addComponent<ColliderComponent>("enemy");

			// Add shooting capability with randomized parameters
			//float randomCooldown = 1.0f + (static_cast<float>(rand()) / RAND_MAX) * 2.0f; // 1-3 seconds
			float randomCooldown = 3.0f;
			enemy.addComponent<ShootingComponent>(
				randomCooldown,
				"Pictures/Bullet_2_Enemy.png",
				"enemyBullet",
				true // Shoot downward
			);

			enemy.addGroup(groupEnemies);
			enemies.push_back(&enemy);
		}
	}

	std::cout << "Spawned " << enemies.size() << " enemies" << std::endl;
}

void EnemySpawner::update() {
	// Update movement pattern

	cleanupInactiveEnemies();
	updateEnemyMovement();

	// Remove any inactive enemies from our list

	// Check if all enemies are destroyed - handled externally now
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
			transform.velocity * -1;;
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
		}
		),
		enemies.end()
	);
}