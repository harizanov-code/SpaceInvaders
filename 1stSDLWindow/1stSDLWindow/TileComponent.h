#pragma once


#include "ECS.h"
#include "SDL3/SDL.h"

class TransformComponent;
class SpriteComponent;

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

    TileComponent() = default;
    TileComponent(int x, int y, int w, int h, int id);

    void init() override;
    void setTileCollision(int id);
};
