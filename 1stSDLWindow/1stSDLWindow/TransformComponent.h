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
	

	float height = 64;
	float width = 64;
	int scale = 1;


	TransformComponent() {
		position.Zero();
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
	void init() override {
		velocity.Zero();
	}

	void update() override {
		previousPosition = position;

		position.x += velocity.x;
		position.y += velocity.y;

		
		// Check if bullet is off-screen (example: off bottom of the screen)
		if (position.y < 0 || position.y > 1280 || position.x < 0 || position.x > 1600) {
			active = false;  // Mark bullet as inactive when it goes off-screen
			entity->destroy();
		}
		
	}



};