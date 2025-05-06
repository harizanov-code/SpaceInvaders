#pragma once


#include "ECS.h"

#include <iostream>
#include "ENUMS.h"

class TransformComponent;

class MouseController : public Component {
public:
    TransformComponent* transform;
    Manager& manager;

    MouseController(Manager& manager);

    void init() override;
    void update() override;
};
