// EnemyFactory.h
#pragma once
#include "ECS.h"

#include <map>

enum class EnemyType {
    SMALL,
    MEDIUM,
    LARGE,
    BOSS
};

struct EnemyConfig {
    const char* spritePath;
    int health;
    int bulletDamage;
    float shootCooldown;
    float moveSpeed;
};

class EnemyFactory {
private:
    static std::map<EnemyType, EnemyConfig> enemyConfigs;

public:
    static void initialize();
    static Entity& createEnemy(Manager& manager, EnemyType type, float x, float y);
};