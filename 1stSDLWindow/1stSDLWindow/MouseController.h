#pragma once
#include "Components.h"
#include "ECS.h"
#include "Game.h"
#include <iostream>
#include "ENUMS.h"

class MouseController : public Component {
public:
    TransformComponent* transform;
    Manager& manager;  


    MouseController(Manager& manager)
        : Component(), manager(manager) {
    }

    void init() override {
     
        transform = &entity->getComponent<TransformComponent>();
    }

    void update() override {
        // Check if mouse button was clicked
        if (Game::event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
            if (Game::event.button.button == SDL_BUTTON_LEFT) {
                // Create a new bullet entity
                auto& bullet(manager.addEntity());

                // Add necessary components to the bullet entity
                bullet.addComponent<TransformComponent>(transform->position.x, transform->position.y);  // Position from player
                bullet.addComponent<SpriteComponent>("Pictures/Bullet_2_Player.png");  // Bullet sprite


                for (auto& entity : manager.entities) {
                    std::cout << "Entity image path : " << entity->getComponent<SpriteComponent>().getPath() << std::endl;
                    std::cout << "Entity pointer: " << &entity << std::endl;
                    std::cout << "Entity X Pos: " << entity->getComponent<TransformComponent>().position.x<< std::endl;
                }

                //bullet.addGroup(groupProjectile);
                // Get the bullet's transform and set its velocity
                auto& bulletTransform = bullet.getComponent<TransformComponent>();
                bulletTransform.velocity.y = -1;
                bulletTransform.velocity.x = 0;
             
            }
        }
    }
};
