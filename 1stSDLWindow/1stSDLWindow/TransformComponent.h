#pragma once

#include "ECS.h"
#include "Components.h"
#include "Vector2D.h"


class TransformComponent : public Component {


public:

	
	Vector2D position;
	Vector2D velocity;
	Vector2D previousPosition;
	

	float speed = 2.0f;
	bool active = true;
	

	float verticalOffset;
	float xMax;
	float yMax;

	float height = 64;
	float width = 64;
	int scale = 1;


	TransformComponent() {
		position.Zero();
		xMax = 1024;
		yMax = 1024;
	}

	TransformComponent(int scale) {
		position.Zero();
		this->scale = scale;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
	TransformComponent(float x, float y, float h, float w, int scale) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		this->scale = scale;
	}
	TransformComponent(float x, float y, float h, float w, int scale, float xMax, float yMax) {
		position.x = x;
		position.y = y;
		height = h;
		width = w;
		this->scale = scale;
		this->xMax = xMax;
		this->yMax = yMax;
	}
	void init() override {
		velocity.Zero();
	}

	void resetWithOffset(float yOffset) {
		this->position.ResetWithOffset(yOffset);
	
	}
		
		void update() override {
		previousPosition = position;

		position.x += velocity.x;
		position.y += velocity.y;

		

		// Check if bullet is off-screen (example: off bottom of the screen)
		if (position.y < 0 || position.y > yMax || position.x < 0 || position.x > xMax) {
			if (entity->getComponent<ColliderComponent>().tag == "bullet" || entity->getComponent<ColliderComponent>().tag == "enemyBullet") {


			std::cout << "Bullet off the screen" << std::endl;
			active = false;  // Mark bullet as inactive
			entity->destroy();

			}
			else {
				resetWithOffset()


			}

		}
		
	}



};