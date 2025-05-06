#include "KeyboardController.h"
#include "SDL3/SDL.h"
#include "Game.h"
#include "TransformComponent.h"

void KeyboardController::init() {
    transform = &entity->getComponent<TransformComponent>();
}

void KeyboardController::update() {
    if (Game::event.type == SDL_EVENT_KEY_DOWN) {
        switch (Game::event.key.key) {
        case SDLK_W:
            transform->velocity.y = -2;
            break;
        case SDLK_S:
            transform->velocity.y = +2;
            break;
        case SDLK_D:
            transform->velocity.x = +2;
            break;
        case SDLK_A:
            transform->velocity.x = -2;
            break;
        default:
            break;
        }
    }

    if (Game::event.type == SDL_EVENT_KEY_UP) {
        switch (Game::event.key.key) {
        case SDLK_W:
            transform->velocity.y = 0;
            break;
        case SDLK_S:
            transform->velocity.y = 0;
            break;
        case SDLK_D:
            transform->velocity.x = 0;
            break;
        case SDLK_A:
            transform->velocity.x = 0;
            break;
        default:
            break;
        }
    }
}
