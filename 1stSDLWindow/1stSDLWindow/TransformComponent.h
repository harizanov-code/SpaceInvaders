#pragma once

#include "ECS.h"
#include "Vector2D.h"
// Forward declarations
class ColliderComponent;
class EnemySpawner;
class Vector2D ;

class TransformComponent : public Component {
public:
    Vector2D position;
    Vector2D velocity;
    Vector2D previousPosition;

    float speed = 2.0f;
    bool active = true;

    float verticalOffset;
    float xMax = 1024;
    float yMax = 1024;

    float height = 64;
    float width = 64;
    int scale = 1;

    TransformComponent();
    explicit TransformComponent(int scale);
    TransformComponent(float x, float y);
    TransformComponent(float x, float y, float h, float w, int scale);
    TransformComponent(float x, float y, float h, float w, int scale, float xMax, float yMax);

    void init() override;
    void update() override;

    void resetWithOffset(float yOffset);
};
