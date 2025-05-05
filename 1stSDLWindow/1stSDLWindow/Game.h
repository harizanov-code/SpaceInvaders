#pragma once

#include "SDL3/SDL.h"
#include <stdio.h>
#include "SDL3_image/SDL_image.h"
#include <vector>
#include <set>
class EnemySpawner;

class ColliderComponent;



class Game {

public :
	Game();
	~Game();
	
	void init(const char* title, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running();

	static void AddTile(int id, int x, int y, std::set<int> collisionTileIdList);
	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;



private:

	EnemySpawner* enemySpawner;
	float deltaTime = 0.0f;
	Uint32 lastFrameTime = 0;
	int width = 0;
	int height = 0;
	bool isRunning;
	int counter = 0;
	SDL_Window* window;

};