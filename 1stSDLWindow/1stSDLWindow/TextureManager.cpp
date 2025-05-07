#include "TextureManager.h"
#include "SDL3/SDL.h"
SDL_Texture* TextureManager::LoadTexture(const char* filePath) {

	SDL_Surface* tempSurface = IMG_Load(filePath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_DestroySurface(tempSurface);

	return tex;

}

void TextureManager::Draw(SDL_Texture* tex, SDL_FRect srcRect, SDL_FRect destRect) {

	SDL_RenderTexture(Game::renderer, tex ,& srcRect, &destRect);
}


void TextureManager::DrawHealthBar(float x, float y, float width, float height, float healthPercent) {
    // Background bar (gray)
    SDL_FRect background = { x, y, width, height };
    SDL_SetRenderDrawColor(Game::renderer, 50, 50, 50, 255);  // Dark gray
    SDL_RenderFillRect(Game::renderer, &background);

    // Health bar (green -> red based on %)
    SDL_FRect health = { x, y, width * healthPercent, height };

    // Interpolate from red to green
    Uint8 red = static_cast<Uint8>((1.0f - healthPercent) * 255);
    Uint8 green = static_cast<Uint8>(healthPercent * 255);

    SDL_SetRenderDrawColor(Game::renderer, red, green, 0, 255);
    SDL_RenderFillRect(Game::renderer, &health);
}
