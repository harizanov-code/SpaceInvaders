#pragma once

#include "Game.h"
#include "ECS.h"
#include "Components.h" 
class KeyboardController : public Component {

public:

	TransformComponent* transform;
	

	void init()override {
		transform = &entity->getComponent<TransformComponent>();
	}
	void update()override {
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
};
