#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <functional>

class UIButton {
public:
    UIButton(int x, int y, const char* fontPath, int fontSize,
        const std::string& label, SDL_Color fg, SDL_Color bg,
        std::function<void()> onClick);

    ~UIButton();

    void draw();
    void handleEvent(const SDL_Event& e);
    void setPosition(int newX, int newY);
    void setLabel(const std::string& newLabel);
    void clean();

private:
    int x, y;
    std::string label;
    const char* fontPath;
    int fontSize;
    TTF_Font* font = nullptr;
    SDL_Texture* tex = nullptr;
    SDL_Color fg;
    SDL_Color bg;
    std::function<void()> onClick;

    void createTexture();
};
