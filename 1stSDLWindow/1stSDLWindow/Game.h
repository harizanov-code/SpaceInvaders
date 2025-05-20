#pragma once

#include "SDL3/SDL.h"
#include <stdio.h>
#include "SDL3_image/SDL_image.h"
#include <vector>
#include <set>
#include "ENUMS.h"

class EnemySpawner;
class ObjectSpawner;
class ColliderComponent;
class ScoreBoard;


enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};


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


	static int enemyCount;
	void reduceEnemyCount();
	static float deltaTime ;
	void setState(GameState newState);
	static GameState gameState;
private:

	void initWindowAndRenderer(const char* title, int width, int height, bool fullscreen);
	void initMap();
	void initPlayer();
	void initUI();
	void initSpawners();
	void initEntities();



	void initMenu();
	void updateMenu();
	void renderMenu();

	void initPlaying();
	void updatePlaying();
	void renderPlaying();

	void initPaused();
	void updatePaused();
	void renderPaused();

	void initGameOver();
	void updateGameOver();
	void renderGameOver();

	void changeStates(GameState newState);

	bool stateInitialized = false;

	ObjectSpawner* objectSpawner;
	ScoreBoard* scoreBoard;
	EnemySpawner* enemySpawner;
	Uint32 lastFrameTime = 0;
	int width = 0;
	int height = 0;
	bool isRunning;
	int counter = 0;
	SDL_Window* window;

};