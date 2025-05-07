// DamageComponent.h
#pragma once
#include "ECS.h"

class DamageComponent : public Component {
public:
    int damageAmount;

    DamageComponent(int amount = 10);

    void init() override;
    void update() override;
};