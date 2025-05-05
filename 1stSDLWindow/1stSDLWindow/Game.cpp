#include "Game.h"
#include "TextureManager.h"
#include <iostream>
#include "GameObject.h"
#include "Map.h"
#include "Components.h"

using std::cout;
using std::endl;

//Map* map;
Manager manager;


SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;


auto& wall(manager.addEntity());
auto& newPlayer(manager.addEntity());
auto& energySpell(manager.addEntity());

enum groupLabels : std::size_t {

	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders,
	groupItems,
	groupProjectile

};


//
//auto& waterTile(manager.addEntity());
//auto& grassTile(manager.addEntity());
//auto& dirtTile(manager.addEntity());


Game::Game() {
}

Game::~Game() {
}

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
	Map::LoadMap("Pictures/Map/p16x16.map",16, 16);

	/*waterTile.addComponent<TileComponent>(200, 200, 64, 64, TileTypes::WATER);
	dirtTile.addComponent<TileComponent>(250, 250,64,64,TileTypes::DIRT);
	dirtTile.addComponent<ColliderComponent>("dirt");
	grassTile.addComponent<TileComponent>(150, 150,64,64,TileTypes::GRASS);
	grassTile.addComponent<ColliderComponent>("grass");*/

	newPlayer.addComponent<TransformComponent>();
	newPlayer.addComponent<SpriteComponent>("Pictures/SpaceShip_1_Player.png");
	newPlayer.addComponent<KeyboardController>();
	newPlayer.addComponent<ColliderComponent>("player");
	newPlayer.addGroup(groupPlayers);


	wall.addComponent<TransformComponent>(256.0f, 256.0f, 64, 12.8f, 5);
	wall.addComponent<SpriteComponent>("Pictures/Tiles/Obstacle_Tile_1.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);


	energySpell.addComponent<TransformComponent>(512.0f, 512.0f, 64, 64, 1);
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

void Game::update() {

	manager.refresh();

	manager.update();

	for (auto cc : colliders) {

		Collision::AABB(newPlayer.getComponent<ColliderComponent>(), *cc);

	}

	//if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, wall.getComponent<ColliderComponent>().collider)) {
	//	//newPlayer.getComponent<TransformComponent>().scale += 0.3;
	//	newPlayer.getComponent<TransformComponent>().velocity* -1;
	//	std::cout << "wall hit " << std::endl;
	//}

	if (Collision::AABB(newPlayer.getComponent<ColliderComponent>().collider, energySpell.getComponent<ColliderComponent>().collider)) {
		newPlayer.getComponent<TransformComponent>().scale += 0.3;
		newPlayer.getComponent<TransformComponent>().velocity.x += 1;
	}

}


auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));
auto& items(manager.getGroup(groupItems));

void Game::render() {

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
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned!" << endl;
}

bool Game::running() {
	return this->isRunning;
}

void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());

	tile.addComponent<TileComponent>(x, y, 64, 64, id);
	tile.addGroup(groupMap);

}

