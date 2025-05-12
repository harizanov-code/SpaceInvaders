#pragma once
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include "ECS.h"
#include "BaseBoard.h"
class ScoreBoard  : public BaseBoard {
private:

	Entity* player;

	
	
public:

	ScoreBoard(Entity* player, int x, int y, const char* fontPath, const char* text, size_t length, SDL_Color fg, SDL_Color bg);
	void init() override;
	void update( ) override;
	void draw() override;
};