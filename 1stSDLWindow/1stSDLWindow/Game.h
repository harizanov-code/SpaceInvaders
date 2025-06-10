#pragma once
#include <functional>
#include "SDL3/SDL.h"
#include <stdio.h>
#include "SDL3_image/SDL_image.h"
#include <vector>
#include <set>
#include "ENUMS.h"
#include <bitset>
class EnemySpawner;
class ObjectSpawner;
class ColliderComponent;
class ScoreBoard;
class PauseMenu;

struct Button {
    SDL_FRect rect;
    std::string label;
    std::function<void()> onClick;
};

enum  GameState {
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
	void cleanState(GameState state);
	static GameState gameState;


private:	


	std::vector<Button> menuButtons;

	std::bitset<4> initializedStates;

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

	void handleMenuEvents();
	void handlePlayingEvents();
	void handlePausedEvents(SDL_Event event);
	void handleGameOverEvents();

	bool stateInitialized = false;

	PauseMenu* pauseMenu;
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