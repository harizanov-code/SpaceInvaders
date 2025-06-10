#pragma once

#include <vector>
#include "UIButton.h"

class PauseMenu {
public:
    PauseMenu(const char* fontPath, int fontSize, SDL_Color fg, SDL_Color bg);
    ~PauseMenu();

    void init();
    void draw();
    void handleEvent(const SDL_Event& e);

private:
    std::vector<UIButton*> buttons;
    const char* fontPath;
    int fontSize;
    SDL_Color fg;
    SDL_Color bg;

    void onContinue();
    void onQuit();
    void onMenu();
};
