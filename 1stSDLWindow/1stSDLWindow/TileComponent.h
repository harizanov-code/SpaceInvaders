#pragma once
#include "Components.h"
#include "ECS.h"
#include "SDL3/SDL.h"


 enum TileType {
	 DIRT,
	GRASS,
	WATER,
	GRAYTILE,
	BLACKTILE,
	

};

class TileComponent : public Component {
public:

	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_FRect tileRect;
	int tileID;
	char* path;
	/*dirt = TextureManager::LoadTexture("Pictures/Tiles/Dirt_Tile_1.png");
	water = TextureManager::LoadTexture("Pictures/Tiles/Water_Tile_1.png");
	grass = TextureManager::LoadTexture("Pictures/Tiles/Grass_Tile_1.png");*/
	TileComponent() = default;
	TileComponent(int x, int y, int w, int h, int id) {

		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
		switch (tileID) {
		case TileType::WATER:
			path = (char *)"Pictures/Tiles/Water_Tile_1.png";
		break; 

		case TileType::GRASS:
			path = (char*)"Pictures/Tiles/Grass_Tile_1.png";
			break;

		case TileType::DIRT:
			path = (char*)"Pictures/Tiles/Dirt_Tile_1.png";
		break;
		case TileType::BLACKTILE:
			path = (char*)"Pictures/Tiles/SpaceInvadersTiles/Black_Tile.png";
		break; 
		case TileType::GRAYTILE:
			path = (char*)"Pictures/Tiles/SpaceInvadersTiles/Gray_Tile.png";

		break; 
		

		default:
			break;
		}


	}

	void init()override {

		entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();

		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();
	}
	void setTileCollision(int id) {


	}


};
