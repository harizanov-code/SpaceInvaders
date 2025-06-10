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
#include "PauseMenu.h"
#include "UIButton.h"

using std::cout;
using std::endl;

//Map* map;
Manager manager;

GameState Game::gameState = PLAYING;



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
	this->initWindowAndRenderer(title, width, height, fullscreen);

}
void Game::handleEvents() {
	SDL_PollEvent(&event);

	// Global events (apply to all states)
	switch (event.type) {
	case SDL_EVENT_QUIT:
		isRunning = false;
		break;

	case SDL_EVENT_KEY_DOWN:
		switch (event.key.key) {
		case SDLK_ESCAPE:
			if (gameState == PLAYING) {
				
				gameState = PAUSED;
			}
			else if (gameState == PAUSED) {
				gameState = PLAYING;
			}
			else if (gameState == MENU) {
				isRunning = false; // Quit game from menu
			}
			break;

		case SDLK_RETURN: // ENTER key
			if (gameState == MENU) {
				gameState = PLAYING;
				// Start game from menu
			}
			else if (gameState == GAME_OVER) {
				gameState = MENU;
			
			}
			break;
		}
		break;
	}

	// State-specific event handling
	if (this->initializedStates.test(gameState)) {
		switch (gameState) {
		case MENU:
			handleMenuEvents();
			break;
		case PLAYING:
			handlePlayingEvents();
			break;
		case PAUSED:
			handlePausedEvents(event);
			break;
		case GAME_OVER:
			handleGameOverEvents();
			break;
		}
	}
}

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& items(manager.getGroup(groupItems));
auto& projectiles(manager.getGroup(groupProjectile));
auto& walls(manager.getGroup(groupWall));

void Game::update() {
	std::cout << "state" << gameState << std::endl;

	// Initialize state if necessary
	if (!this->initializedStates.test(gameState)) {

		std::cout << "state" << gameState << std::endl;
		std::cout << "WE are here initializing again" << this->initializedStates.test(gameState) << std::endl;


		switch (gameState) {
		case MENU:
			initMenu();
			break;
		case PLAYING:
			initPlaying();
			break;
		case PAUSED:
			initPaused();
			break;
		case GAME_OVER:
			initGameOver();
			break;
		}

		setState(gameState);

	}

	// Update based on current state
	switch (gameState) {
	case MENU:
		updateMenu();
		break;
	case PLAYING:
		updatePlaying();



		break;
	case PAUSED:
		updatePaused();
		break;
	case GAME_OVER:
		updateGameOver();
		break;
	}



}




void Game::render() {

	SDL_RenderClear(renderer);

	// Render based on current state
	switch (gameState) {
	case MENU:
		renderMenu();
		break;
	case PLAYING:
		renderPlaying();
		break;
	case PAUSED:
		renderPaused();
		break;
	case GAME_OVER:
		renderGameOver();
		break;
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete enemySpawner;
	delete objectSpawner;
	delete scoreBoard;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
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
	if (gameState != newState) {
		// Don't clean PAUSED or if resuming from pause
		if (!(gameState == PLAYING && newState == PAUSED) &&
			!(gameState == PAUSED && newState == PLAYING)) {

			std::cout << "Cleaned on set state" << std::endl;
			cleanState(gameState);
		}

		gameState = newState;

	}

	if (!initializedStates.test(newState)) {
		initializedStates.set(newState);
		// Optionally call initState(newState);
	}
}


void Game::cleanState(GameState state) {
	switch (state) {
	case PLAYING:
		// Clean gameplay-specific entities and resources
		manager.refresh();
		for (auto& e : manager.entities) {
			e->destroy();
		}
		Game::colliders.clear();
		Game::enemyCount = 0;

		if (enemySpawner) {
			delete enemySpawner;
			enemySpawner = nullptr;
		}

		if (objectSpawner) {
			delete objectSpawner;
			objectSpawner = nullptr;
		}

		if (scoreBoard) {
			delete scoreBoard;
			scoreBoard = nullptr;
		}

		break;

	case MENU:
		// Clean menu-specific resources if any
		break;

	case PAUSED:
		// Usually no cleanup here
		break;

	case GAME_OVER:
		// Optional: if GAME_OVER has separate resources
		break;

	default:
		break;
	}

	// Reset initialization flag for that state so it can be re-initialized later if needed
	this->initializedStates.reset(state);
}


void Game::initWindowAndRenderer(const char* title, int width, int height, bool fullscreen) {
	// First, initialize SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		isRunning = false;
		return;
	}

	// Then set window flags
	int windowFlags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;

	// Create window
	this->window = SDL_CreateWindow(title, width, height, windowFlags);
	if (!window) {
		isRunning = false;
		return;
	}

	this->height = height;
	this->width = width;

	// Create renderer
	this->renderer = SDL_CreateRenderer(window, NULL);
	if (!renderer) {
		isRunning = false;
		return;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	isRunning = true;
	gameState = PLAYING;
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
	menuButtons.clear();

	std::cout << "Init menu " << std::endl;
	// Define Play button
	Button playButton;
	playButton.rect = { 300, 200, 200, 50 };
	playButton.label = "Play";
	playButton.onClick = [this]() {
		setState(PLAYING);
	};

	// Define Quit button
	Button quitButton;
	quitButton.rect = { 300, 300, 200, 50 };
	quitButton.label = "Quit";
	quitButton.onClick = [this]() {
		isRunning = false;
	};

	menuButtons.push_back(playButton);
	menuButtons.push_back(quitButton);
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








	for (auto& btn : menuButtons) {
		// Draw button background
		SDL_SetRenderDrawColor(renderer, 70, 130, 180, 255); // steel blue
		SDL_RenderFillRect(renderer, &btn.rect);

		// Optional: draw border
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderRect(renderer, &btn.rect);

		// Draw text (placeholder - needs SDL_ttf for actual text)
		// renderText(btn.label, btn.rect.x + 10, btn.rect.y + 10);
	}

	SDL_RenderPresent(renderer);



	//whichever is rendered first appears on the background and the rest of the stuff is on top
	//this is where we add stuff to the renderer
	//map->DrawMap();


}

void Game::initPlaying() {

	std::cout << "state" << gameState << std::endl;
	std::cout << "WE are here initializing playing" << this->initializedStates.test(gameState) << std::endl;


	setState(gameState);

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
void Game::initPaused() {


	std::cout << "Created Pause menu" << std::endl;
	SDL_Color textColor = { 255, 255, 255, 255 };
	SDL_Color bgColor = { 0, 0, 0, 0 };

	pauseMenu = new PauseMenu("./Pictures/Fonts/Roboto-VariableFont.ttf",24,
		bgColor, textColor);
	pauseMenu->init();
}

void Game::updatePaused() {
	
	pauseMenu->draw();

}
void Game::renderPaused() {

	pauseMenu->draw();


	SDL_RenderPresent(renderer);


}
void Game::initGameOver() {

}
void Game::updateGameOver() {

}
void Game::renderGameOver() {


}
void Game::changeStates(GameState newState) {

}

void Game::handleMenuEvents() {
	if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
		int mouseX = event.button.x;
		int mouseY = event.button.y;


		SDL_FPoint point = { mouseX, mouseY };
		for (auto& btn : menuButtons) {
			if (SDL_PointInRectFloat(&point, &btn.rect)) {
				btn.onClick(); // Trigger button action
				break;
			}
		}
	}
}

void Game::handlePausedEvents(SDL_Event event) {

	pauseMenu->handleEvent(event);


}

void Game::handlePlayingEvents() {


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

void Game::handleGameOverEvents() {

}


