#include "EnemyFactory.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"
#include "ShootingComponent.h"
#include "ENUMS.h"


std::map<EnemyType, EnemyConfig> EnemyFactory::enemyConfigs;

void EnemyFactory::initialize() {
    // Define enemy configurations
    enemyConfigs[EnemyType::SMALL] = { "Pictures/Enemies/Enemy_Level1_Cloud.png", 20, 10, 3.0f, 1.0f };
    enemyConfigs[EnemyType::MEDIUM] = { "Pictures/Enemies/Enemy_Level2_Bee.png", 40, 20, 2.5f, 0.8f };
    enemyConfigs[EnemyType::LARGE] = { "Pictures/Enemies/Enemy_Level3_Bean.png", 80, 30, 2.0f, 0.6f };
    enemyConfigs[EnemyType::BOSS] = { "Pictures/Enemies/Enemy_Boss_Eye_1.png", 200, 50, 1.5f, 0.4f };
}

Entity& EnemyFactory::createEnemy(Manager& manager, EnemyType type, float x, float y) {
    auto& enemy = manager.addEntity();

    // If configs haven't been initialized, do so now
    if (enemyConfigs.empty()) {
        initialize();
    }

    const auto& config = enemyConfigs[type];

    // Add basic components
    enemy.addComponent<TransformComponent>(x, y, 64, 64, 1, 1024, 1024);
    enemy.getComponent<TransformComponent>().velocity.x = config.moveSpeed;
    enemy.addComponent<SpriteComponent>(config.spritePath);
    enemy.addComponent<ColliderComponent>("enemy");

    // Add health with type-specific values
    enemy.addComponent<HealthComponent>(config.health);

    // Add shooting with type-specific values
    auto& shooting = enemy.addComponent<ShootingComponent>(
        config.shootCooldown,
        "Pictures/Bullet_2_Enemy.png",
        "enemyBullet",
        true // Shoot downward
    );
    shooting.setBulletDamage(config.bulletDamage);

    enemy.addGroup(groupEnemies);

    return enemy;
}