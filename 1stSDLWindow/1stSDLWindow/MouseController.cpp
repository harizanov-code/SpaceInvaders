#include "MouseController.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Game.h"

MouseController::MouseController(Manager& manager)
    : Component(), manager(manager) {
}

void MouseController::init() {
    transform = &entity->getComponent<TransformComponent>();
}

void MouseController::update() {
    // Check if mouse button was clicked
    if (Game::event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        if (Game::event.button.button == SDL_BUTTON_LEFT) {
            // Create a new bullet entity
            auto& bullet(manager.addEntity());

            // Add necessary components to the bullet entity
            bullet.addComponent<TransformComponent>(transform->position.x, transform->position.y);  // Position from player
            bullet.addComponent<SpriteComponent>("Pictures/Bullet_2_Player.png");  // Bullet sprite

            for (auto& entity : manager.entities) {
               }

            // Get the bullet's transform and set its velocity
            auto& bulletTransform = bullet.getComponent<TransformComponent>();
            bulletTransform.velocity.y = -1;
            bulletTransform.velocity.x = 0;
        }
    }
}
