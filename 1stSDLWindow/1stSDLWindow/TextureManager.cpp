#include "TextureManager.h"

SDL_Texture* TextureManager::LoadTexture(const char* filePath) {

	SDL_Surface* tempSurface = IMG_Load(filePath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_DestroySurface(tempSurface);

	return tex;

}

void TextureManager::Draw(SDL_Texture* tex, SDL_FRect srcRect, SDL_FRect destRect) {

	SDL_RenderTexture(Game::renderer, tex ,& srcRect, &destRect);
}
