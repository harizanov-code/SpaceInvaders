#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>

Map::Map() {

}
Map::~Map() {

  
}
void Map::LoadMap( std::string path, int sizeX, int sizeY) {
    std::ifstream mapFile(path);
    if (!mapFile.is_open()) {
        std::cerr << "Failed to open map file: " << path << std::endl;
        return;
    }

    char tile;
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            do {
                mapFile.get(tile);
            } while (tile == '\n' || tile == '\r' || tile == ' '); 


            Game::AddTile(atoi(&tile), x * 64, y * 64);

         
            mapFile.ignore(1);
        }
    }

    mapFile.close();
}


