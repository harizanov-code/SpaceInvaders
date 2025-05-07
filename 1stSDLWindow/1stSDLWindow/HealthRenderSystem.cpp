#include "HealthRenderSystem.h"
#include "HealthComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include <SDL3/SDL.h>

void HealthRenderSystem::Draw(Manager& manager) {
    for (auto& entity : manager.entities) {
        if (entity->hasComponent<HealthComponent>() && entity->hasComponent<TransformComponent>()) {
            auto& health = entity->getComponent<HealthComponent>();
            auto& transform = entity->getComponent<TransformComponent>();

            float healthPercent = health.getHealthPercent();
            float width = transform.width * transform.scale;
            float height = 5.0f;
            float x = transform.position.x;
            float y = transform.position.y - height - 2.0f;

            // Draw background (gray)
            SDL_FRect bg = { x, y, width, height };
            SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);
            SDL_RenderFillRect(Game::renderer, &bg);

            // Draw health bar (gradient from green to red)
            SDL_FRect hp = { x, y, width * healthPercent, height };
            Uint8 red = static_cast<Uint8>((1.0f - healthPercent) * 255);
            Uint8 green = static_cast<Uint8>(healthPercent * 255);
            SDL_SetRenderDrawColor(Game::renderer, red, green, 0, 255);
            SDL_RenderFillRect(Game::renderer, &hp);
        }
    }
}
