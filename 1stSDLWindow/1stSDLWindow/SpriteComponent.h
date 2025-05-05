#pragma once

#include "Components.h"
#include "SDL3/SDL.h"
#include "iostream"
#include "TextureManager.h"



class SpriteComponent : public Component {
private:

	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_FRect srcRect, destRect;

	const char* path;
public:

	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		this->path = path;
		setText(path);
	}
	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}


	void setText(const char* path) {

		texture = TextureManager::LoadTexture(path);
	}

	void init()override {

		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;


		//destRect.x = destRect.y = 0;
		//destRect.w = transform->width * transform->scale;
		//destRect.h = transform->height* transform->scale;

	}

	void update()override {
		destRect.x = transform->position.x;
		destRect.y = transform->position.y;
		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;


	}
	void draw()override {
	
		TextureManager::Draw(texture, srcRect, destRect);
	}

	const char* getPath() {

		return path;
	}

};

