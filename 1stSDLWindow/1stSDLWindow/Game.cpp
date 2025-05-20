#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include "GameObject.h"
#include "Map.h"
#include "ColliderComponent.h"
#include "EnemySpawner.h"
#include "ENUMS.h"
#include "KeyboardController.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "Collision.h"
#include "TileComponent.h"
#include "ObjectSpawner.h"
#include "HealthComponent.h"
#include "HealthRenderSystem.h"
#include "DamageComponent.h"
#include "ScoreBoard.h"
using std::cout;
using std::endl;

//Map* map;
Manager manager;
GameState gameState;



SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;







auto& wall(manager.addEntity());
auto& newPlayer(manager.addEntity());
auto& energySpell(manager.addEntity());




//
//auto& waterTile(manager.addEntity());
//auto& grassTile(manager.addEntity());
//auto& dirtTile(manager.addEntity());


Game::Game() {
}

Game::~Game() {
}

float Game::deltaTime = 1.0f;
int Game::enemyCount = 0;

void Game::init(const char* title, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {

		flags = SDL_WINDOW_FULLSCREEN;
	}
	else {
		flags = NULL;
	}
	if (SDL_Init(flags)) {

		std::cout << "Subsystem init" << std::endl;
		this->window = SDL_CreateWindow(title, width, height, flags);
		if (window) {
			this->height = height;
			this->width = width;
			cout << "Window has been created!" << endl;
		}

		this->renderer = SDL_CreateRenderer(window, NULL);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer has been created!" << endl;
		}
		isRunning = true;
	}
	else {
		isRunning = false;
	}

	//player = new GameObject("Pictures/SpaceShip_1_Player.png"	, 0 ,400);
		//enemy = new GameObject("Pictures/Enemies/Enemy_Level1_Cloud.png"	, 0 ,0);
	
	//space Invaders map
	Map::LoadMap("Pictures/Map/p16x16_Level1.map",16, 16);
	 
	 //rpg game map
	//Map::LoadMap("Pictures/Map/p16x16.map",16, 16);

	/*waterTile.addComponent<TileComponent>(200, 200, 64, 64, TileTypes::WATER);
	dirtTile.addComponent<TileComponent>(250, 250,64,64,TileTypes::DIRT);
	dirtTile.addComponent<ColliderComponent>("dirt");
	grassTile.addComponent<TileComponent>(150, 150,64,64,TileTypes::GRASS);
	grassTile.addComponent<ColliderComponent>("grass");*/

	newPlayer.addComponent<TransformComponent>(0.0f, 950.0f);
	newPlayer.addComponent<SpriteComponent>("Pictures/SpaceShip_1_Player.png");
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);
	newPlayer.addComponent<HealthComponent>();
	// In Game.cpp init:
	SDL_Color textColor = { 255, 255, 255, 255 };  // White
	SDL_Color bgColor = { 0, 0, 0, 0 };         // Semi-transparent black


	scoreBoard = new ScoreBoard(&newPlayer,0,0, "./Pictures/Fonts/Roboto-VariableFont.ttf",
		"Health: 100 | Enemies: 0", 100, bgColor,textColor);
	scoreBoard->init();

	enemySpawner = new EnemySpawner(manager);
	enemySpawner->spawnEnemyFormation();

	objectSpawner = new ObjectSpawner(manager);





	energySpell.addComponent<TransformComponent>(950.0f, 950.0f, 64, 64, 1);
	energySpell.addComponent<SpriteComponent>("Pictures/Objects/Energy_Object_1.png");
	energySpell.addComponent<ColliderComponent>("energySpell");
	energySpell.addGroup(groupItems);



}
void Game::handleEvents() {
	SDL_PollEvent(&event);

	switch (event.type) {
	case SDL_EVENT_QUIT:
		isRunning = false;
		break;
	case SDL_EVENT_MOUSE_BUTTON_DOWN:
		if (Game::event.button.button == SDL_BUTTON_LEFT) {
			// Check if we already have fewer than 3 active bullets
			int activeBulletCount = 0;
			for (auto& entity : manager.entities) {


				if (entity->hasComponent<ColliderComponent>() && (entity->getComponent<ColliderComponent>().tag == "bullet")) {

					if (entity->hasComponent<TransformComponent>() &&
						entity->getComponent<TransformComponent>().active)
						std::cout << "IAM Active" << std::endl;

					activeBulletCount++;
				}
			}


			if (activeBulletCount < 3) {


				auto& bullet = manager.addEntity();

				// Add necessary components to the bullet entity
				bullet.addComponent<TransformComponent>(newPlayer.getComponent<TransformComponent>().position.x,
					newPlayer.getComponent<TransformComponent>().position.y);
				bullet.addComponent<ColliderComponent>("bullet");
				bullet.addComponent<SpriteComponent>("Pictures/Bullet_2_Player.png");
				bullet.addGroup(groupProjectile);


				auto& bulletTransform = bullet.getComponent<TransformComponent>();
				bulletTransform.velocity.y = -10;
				bulletTransform.velocity.x = 0;
			}
		}
		break;
	default:
		break;
	}
}
auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& items(manager.getGroup(groupItems));
auto& projectiles(manager.getGroup(groupProjectile));
auto& walls(manager.getGroup(groupWall));

void Game::update() {

	// Initialize state if necessary
	if (!stateInitialized) {
		switch (gameState) {
		case GameState::MENU:
			initMenu();
			break;
		case GameState::PLAYING:
			initPlaying();
			break;
		case GameState::PAUSED:
			initPaused();
			break;
		case GameState::GAME_OVER:
			initGameOver();
			break;
		}
		stateInitialized = true;
	}

	// Update based on current state
	switch (gameState) {
	case GameState::MENU:
		updateMenu();
		break;
	case GameState::PLAYING:
		updatePlaying();



		break;
	case GameState::PAUSED:
		updatePaused();
		break;
	case GameState::GAME_OVER:
		updateGameOver();
		break;
	}



}




void Game::render() {
}

void Game::clean() {
	delete enemySpawner;
	delete objectSpawner;
	delete scoreBoard;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned!" << endl;
}

bool Game::running() {
	return this->isRunning;
}

void Game::AddTile(int id, int x, int y, std::set<int>  collisionTileIdList) {
	auto& tile(manager.addEntity());

	tile.addComponent<TileComponent>(x, y, 64, 64, id);
	tile.addGroup(groupMap);

	for (int i : collisionTileIdList) {

		if (id == i) {
			tile.addComponent<ColliderComponent>("wall");
			tile.addGroup(groupWall);

		}
	}
	

}

void Game::reduceEnemyCount() {

	Game::enemyCount--;
}

void Game::setState(GameState newState) {

	if (gameState == newState) return;

	if (gameState == GameState::PLAYING) {

		//here I should clean the current game stuff
	}

	gameState = newState;
	stateInitialized = false;
}


void Game::initWindowAndRenderer(const char* title, int width, int height, bool fullscreen) {
	int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	if (SDL_Init(flags) == 0) {
		window = SDL_CreateWindow(title, width, height, flags);
		if (window) {
			this->width = width;
			this->height = height;
			std::cout << "Window has been created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, NULL);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer has been created!" << std::endl;
		}

		isRunning = true;
	}
	else {
		std::cout << "Subsystem init failed!" << std::endl;
		isRunning = false;
	}
}

void Game::initMap() {
	Map::LoadMap("Pictures/Map/p16x16_Level1.map", 16, 16);
}


void Game::initPlayer() {
	newPlayer.addComponent<TransformComponent>(0.0f, 950.0f);
	newPlayer.addComponent<SpriteComponent>("Pictures/SpaceShip_1_Player.png");
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addComponent<HealthComponent>();
	newPlayer.addGroup(groupPlayers);
}

void Game::initUI() {
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Color bgColor = { 0, 0, 0, 0 };

	scoreBoard = new ScoreBoard(&newPlayer, 0, 0,
		"./Pictures/Fonts/Roboto-VariableFont.ttf",
		"Health: 100 | Enemies: 0", 100, bgColor, textColor);
	scoreBoard->init();
}

void Game::initSpawners() {
	enemySpawner = new EnemySpawner(manager);
	enemySpawner->spawnEnemyFormation();

	objectSpawner = new ObjectSpawner(manager);
}

void Game::initEntities() {
	energySpell.addComponent<TransformComponent>(950.0f, 950.0f, 64, 64, 1);
	energySpell.addComponent<SpriteComponent>("Pictures/Objects/Energy_Object_1.png");
	energySpell.addComponent<ColliderComponent>("energySpell");
	energySpell.addGroup(groupItems);
}



void Game::updatePlaying() {

	manager.refresh();
	manager.update();



	Uint32 currentTime = SDL_GetTicks();
	deltaTime = (currentTime - lastFrameTime) / 1000.0f;
	lastFrameTime = currentTime;

	enemySpawner->update();

	if (enemySpawner->allEnemiesDestroyed()) {
		enemySpawner->spawnEnemyFormation();
	}

	for (auto cc : colliders) {
		Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);
	}


	for (auto& wallEntity : walls) {
		if (Collision::AABB(
			newPlayer.getComponent<ColliderComponent>().collider,
			wallEntity->getComponent<ColliderComponent>().collider)) {
			newPlayer.getComponent<TransformComponent>().position =
				newPlayer.getComponent<TransformComponent>().previousPosition;
			newPlayer.getComponent<TransformComponent>().velocity = { 0, 0 };

			std::cout << "Wall hit\n";
		}


	}


	for (auto& wallEntity : walls) {
		if (Collision::AABB(
			newPlayer.getComponent<ColliderComponent>().collider,
			wallEntity->getComponent<ColliderComponent>().collider)) {
			newPlayer.getComponent<TransformComponent>().position =
				newPlayer.getComponent<TransformComponent>().previousPosition;
			newPlayer.getComponent<TransformComponent>().velocity = { 0, 0 };

			std::cout << "Wall hit\n";
		}
		for (auto& projectile : projectiles) {

			if (Collision::AABB(wallEntity->getComponent<ColliderComponent>().collider, projectile->getComponent<ColliderComponent>().collider)) {


				projectile->destroy();

			}
		}


	}

	if (Collision::AABB(
		newPlayer.getComponent<ColliderComponent>().collider,
		energySpell.getComponent<ColliderComponent>().collider)) {
		newPlayer.getComponent<TransformComponent>().scale += 0.3;
		newPlayer.getComponent<TransformComponent>().velocity.x += 1;
	}

	for (auto& projectile : projectiles) {
		if (projectile->hasComponent<ColliderComponent>() &&
			projectile->getComponent<ColliderComponent>().tag == "enemyBullet") {

			if (Collision::AABB(
				newPlayer.getComponent<ColliderComponent>().collider,
				projectile->getComponent<ColliderComponent>().collider)) {

				// Get damage amount
				int damage = 10; // Default
				if (projectile->hasComponent<DamageComponent>()) {
					damage = projectile->getComponent<DamageComponent>().damageAmount;
				}

				// Apply damage to player
				bool playerDied = newPlayer.getComponent<HealthComponent>().takeDamage(damage);
				std::cout << "Player hit by enemy bullet! Remaining health: "
					<< newPlayer.getComponent<HealthComponent>().currentHealth << std::endl;

				// Handle player death if needed
				if (playerDied) {
					// Game over logic
					std::cout << "Player died! Game over!" << std::endl;
					// You could add game over screen or restart logic here
				}

				// Destroy the bullet
				projectile->destroy();
			}
		}
	}

	for (auto& p1 : projectiles) {
		if (!p1->isActive()) continue;

		bool isPlayerBullet = p1->getComponent<ColliderComponent>().tag == "bullet";

		for (auto& p2 : projectiles) {
			if (!p2->isActive() || p1 == p2) continue;

			bool isEnemyBullet = p2->getComponent<ColliderComponent>().tag == "enemyBullet";


			if (isPlayerBullet && isEnemyBullet) {
				if (Collision::AABB(
					p1->getComponent<ColliderComponent>().collider,
					p2->getComponent<ColliderComponent>().collider)) {

					p1->destroy();
					p2->destroy();
					break;
				}
			}
		}
	}

	for (auto& projectile : projectiles) {
		if (!projectile->isActive() ||
			projectile->getComponent<ColliderComponent>().tag != "bullet") {
			continue;
		}

		for (auto& enemy : enemies) {
			if (!enemy->isActive()) continue;

			if (Collision::AABB(
				projectile->getComponent<ColliderComponent>().collider,
				enemy->getComponent<ColliderComponent>().collider)) {

				// Get damage amount
				int damage = 10; // Default
				if (projectile->hasComponent<DamageComponent>()) {
					damage = projectile->getComponent<DamageComponent>().damageAmount;
				}

				// Apply damage to enemy
				bool enemyDied = enemy->getComponent<HealthComponent>().takeDamage(damage);

				// Always destroy the bullet
				projectile->destroy();

				// Handle enemy death
				if (enemyDied) {
					Game::reduceEnemyCount();
					std::cout << "Enemy destroyed!" << std::endl;
					enemy->destroy();
					objectSpawner->spawnObject(enemy);
				}

				break;
			}
		}
	}
	scoreBoard->update();
}

void Game::initMenu() {
	// Initialize only what's needed for the menu
	initWindowAndRenderer("ELDER SCROLLS MENU", 1024, 1024, false);

	// Create menu buttons/UI elements
	// You might need a MenuComponent or similar class
}

void Game::updateMenu() {
	// Process menu-specific logic
	// Handle menu button clicks, selections, etc.

	// Example of state transition
	/*if (menuStartButtonClicked) {
		setState(GameState::PLAYING);
	}*/
}

void Game::renderMenu() {



	SDL_RenderClear(renderer);
	//whichever is rendered first appears on the background and the rest of the stuff is on top
	//this is where we add stuff to the renderer
	//map->DrawMap();


	for (auto* t : tiles) {

		t->draw();
	}


	for (auto* p : players) {
		p->draw();
	}
	for (auto* e : enemies) {
		e->draw();
	}
	for (auto* i : items) {
		i->draw();
	}for (auto* p : projectiles) {
		p->draw();
	}
	HealthRenderSystem::Draw(manager);

	scoreBoard->draw();
	SDL_RenderPresent(renderer);
}

void Game::initPlaying() {
	// Initialize game elements needed for playing state
	initMap();
	initPlayer();
	initUI();
	initSpawners();
	initEntities();
}



void Game::renderPlaying() {
	for (auto* t : tiles) {
		t->draw();
	}
	for (auto* p : players) {
		p->draw();
	}
	
}