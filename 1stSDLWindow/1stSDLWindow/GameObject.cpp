#include "GameObject.h"
#include "TextureManager.h"
#include <iostream>

GameObject::GameObject(const char* textureSheet,int x , int y) {
	
	std::cout << "file" << textureSheet << std::endl;
	objTexture = TextureManager::LoadTexture(textureSheet);

	xpos = x;
	ypos = y;
}

GameObject::~GameObject() {
}

void GameObject::Update() {
	xpos++;
	//ypos++;

	srcRect.h = 64;
	srcRect.w = 96;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.h = srcRect.h ;
	destRect.w = srcRect.w  ;



}

void GameObject::Render() {

	SDL_RenderTexture(Game::renderer, objTexture, &srcRect, &destRect);

}
