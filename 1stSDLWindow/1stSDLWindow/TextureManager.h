#pragma once
#include "Game.h"
#include "SDL3_ttf/SDL_ttf.h"

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* filePath);
	static SDL_Texture* LoadTextTexture(TTF_Font* font, const char* text, size_t lenght, SDL_Color fg, SDL_Color bg);

	static void Draw(SDL_Texture* tex, SDL_FRect srcRect, SDL_FRect destRect);
};