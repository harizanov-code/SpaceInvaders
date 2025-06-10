#include "PauseMenu.h"
#include "Game.h"  // Assuming you have Game states in here
#include <iostream>

PauseMenu::PauseMenu(const char* fontPath, int fontSize, SDL_Color fg, SDL_Color bg)
    : fontPath(fontPath), fontSize(fontSize), fg(fg), bg(bg) {
}

PauseMenu::~PauseMenu() {
    for (auto btn : buttons) {
        delete btn;
    }
    buttons.clear();
}

void PauseMenu::init() {
    int startX = 300;
    int startY = 200;
    int spacingY = 60;
    
    
    buttons.push_back(new UIButton(startX, startY, fontPath, fontSize, "Continue", fg, bg,
        [this]() { onContinue(); }));

    buttons.push_back(new UIButton(startX, startY + spacingY, fontPath, fontSize, "Menu", fg, bg,
        [this]() { onMenu(); }));

    buttons.push_back(new UIButton(startX, startY + spacingY * 2, fontPath, fontSize, "Quit", fg, bg,
        [this]() { onQuit(); }));
}

void PauseMenu::draw() {
    for (auto btn : buttons) {
        btn->draw();
    }
}

void PauseMenu::handleEvent(const SDL_Event& e) {
    for (auto btn : buttons) {
        btn->handleEvent(e);
    }
}

void PauseMenu::onContinue() {
    std::cout << "Continue clicked\n";
   
    Game::gameState = PLAYING;// Or whatever your enum/state switch is
}

void PauseMenu::onMenu() {
    std::cout << "Menu clicked\n";
   
    Game::gameState = MENU;// Or whatever your enum/state switch is


}

void PauseMenu::onQuit() {
    std::cout << "Quit clicked\n";
   // Game::quit();  // Your quit function or just exit
}
