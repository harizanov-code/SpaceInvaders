#include "ScoreBoard.h"
#include "TextureManager.h"
#include "HealthComponent.h"
#include  <cstdio>
#include <string>
#include <fstream>
#include <filesystem>


ScoreBoard::ScoreBoard(Entity* player,int x , int y, const char* fontPath, const char* text, size_t length, SDL_Color fg, SDL_Color bg) : BaseBoard(x, y , fontPath,fg,bg, text, length){

    this->player = player;	
	
}

void ScoreBoard::init() {

    if(TTF_Init() == -1) {
        std::cout << "Couldn't initialize " << std::endl;

    }


 
    font = TTF_OpenFont(fontPath, 24);  // 24 is the font size

    if (!font) {
        std::cerr << "Failed to load font: "  << std::endl;
        // Try with a different font size
        font = TTF_OpenFont(fontPath, 12);
        if (!font) {
            std::cerr << "Still failed with smaller size: "  << std::endl;
            return;
        }
    }
    else {
        std::cout << "Font loaded successfully!" << std::endl;
    }

    // Now render the text
    currentText = text;
    SDL_Surface* textSurface = TTF_RenderText_Shaded(font, currentText.c_str(),length, fg, bg);

    if (!textSurface) {
        std::cerr << "Failed to render text surface: "  << std::endl;
        return;
    }

    tex = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
    SDL_DestroySurface(textSurface);

    if (!tex) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }
    else {
        std::cout << "Scoreboard text rendered successfully!" << std::endl;
    }
}
void ScoreBoard::update() {

        // Get components (example assumes components for Health, Points)
        auto& health = player->getComponent<HealthComponent>().currentHealth;
        //auto& points = player->getComponent<PointsComponent>().points;

        // Get global enemy count from your Game or ECS system
        int totalEnemies = Game::enemyCount; // You define this somewhere globally or inject into ScoreBoard

        // Build text
        /*    " | Score: " + std::to_string(points) +*/
        std::string newText = "Health: " + std::to_string(health) +
            " | Enemies: " + std::to_string(totalEnemies);

        // Only update if changed
        if (newText != currentText) {
            currentText = newText;

            // Clean old texture
            if (tex) SDL_DestroyTexture(tex);

            // Create new texture
            tex = TextureManager::LoadTextTexture(font, currentText.c_str(), currentText.size(), fg, bg);
        }
    




}


void ScoreBoard::draw() {
    if (!tex) return;

    std::cout << "Drawing score board " << std::endl;

    float textW, textH;
    SDL_GetTextureSize(tex, &textW, &textH);
    std::cout << "WIDHT AND HEIGHT" << textW << "---" << textH << std::endl;
    SDL_FRect srcRect = { 0, 0, textW, textH };
    SDL_FRect destRect = { static_cast<float>(x) , static_cast<float>(y), textW, textH };

    TextureManager::Draw(tex, srcRect, destRect);

}