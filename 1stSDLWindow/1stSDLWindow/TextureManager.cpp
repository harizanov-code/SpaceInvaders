#include "TextureManager.h"
#include "SDL3/SDL.h"
SDL_Texture* TextureManager::LoadTexture(const char* filePath) {

	SDL_Surface* tempSurface = IMG_Load(filePath);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_DestroySurface(tempSurface);

	return tex;

}

SDL_Texture* TextureManager::LoadTextTexture(TTF_Font* font, const char* text, size_t length, SDL_Color fg, SDL_Color bg) {
    
    SDL_Surface* tempSurface = TTF_RenderText_Shaded(font, text,length,fg, bg);
    //SDL_Surface* tempSurface = TTF_RenderText_Solid(font, text, length, fg);
    if (!tempSurface) {
       
        SDL_Log("Failed to render text surface: %s\n");
        return nullptr;
    }

   
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
    if (!tex) {
     
        SDL_Log("Failed to create texture from surface: %s\n", SDL_GetError());
    }


    SDL_DestroySurface(tempSurface);

    return tex;
}


void TextureManager::Draw(SDL_Texture* tex, SDL_FRect srcRect, SDL_FRect destRect) {

	SDL_RenderTexture(Game::renderer, tex ,& srcRect, &destRect);
}

