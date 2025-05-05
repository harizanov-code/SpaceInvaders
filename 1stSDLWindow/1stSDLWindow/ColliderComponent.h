#pragma once 
#include <string>
#include "SDL3/SDL.h"
#include "Components.h"
#include <iostream>
#include "Game.h"
class ColliderComponent : public Component {

public:
	SDL_FRect collider;
	std::string tag;

	TransformComponent* transform;

	ColliderComponent(std::string tag) {
		
		this->tag = tag;
	}
		void init() override {
			if (!entity->hasComponent<TransformComponent>()) {

				entity->addComponent<TransformComponent>();
			}

			transform = &entity->getComponent<TransformComponent>();

			Game::colliders.emplace_back(std::move(this));

	} 

		void update()override {

			collider.x = transform->position.x;
			collider.y = transform->position.y;
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
		}


		std::string getTag()  {

			return this->tag;
		}
};