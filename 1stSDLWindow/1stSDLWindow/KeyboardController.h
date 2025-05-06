#pragma once


#include "ECS.h"

class TransformComponent;

class KeyboardController : public Component {
public:
    TransformComponent* transform;

    void init() override;
    void update() override;
};
