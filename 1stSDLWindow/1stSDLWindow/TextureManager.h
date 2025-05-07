#pragma once
#include "Game.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* filePath);

	static void DrawHealthBar(float x, float y, float width, float height, float healthPercent);
	static void Draw(SDL_Texture* tex, SDL_FRect srcRect, SDL_FRect destRect);
};