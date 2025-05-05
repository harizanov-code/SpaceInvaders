#include "Map.h"
#include "Game.h"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>



Map::Map() {

}
Map::~Map() {

  
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) {
    std::ifstream mapFile(path);
    if (!mapFile.is_open()) {
        std::cerr << "Failed to open map file: " << path << std::endl;
        return;
    }

    std::set<int> collisionIDs;

    // Read optional collision list at the top
    std::string line;

    auto trim = [](std::string& s) {
        s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    };

    if (std::getline(mapFile, line)) {
        if (line.find("collision list") != std::string::npos) {
            std::size_t start = line.find('[');
            std::size_t end = line.find(']');
            if (start != std::string::npos && end != std::string::npos && end > start) {
                std::string ids = line.substr(start + 1, end - start - 1);
                std::stringstream ss(ids);
                int id;
                while (ss >> id) {
                    collisionIDs.insert(id);
                    if (ss.peek() == ',') ss.ignore(); // skip commas
                }
            }
        }
    }



    char tile;
    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            do {
                mapFile.get(tile);
            } while (tile == '\n' || tile == '\r' || tile == ' ');

            int tileID = atoi(&tile);
            Game::AddTile(tileID, x * 64, y * 64, collisionIDs);

          

            mapFile.ignore(1);
        }
    }

    mapFile.close();
}
void Map::SetCollisionTile(int id) {


}


