#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

class BaseBoard {
protected:
    int x;
    int y;
    std::string currentText;
    SDL_Texture* tex = nullptr;
    const char* fontPath;
    TTF_Font* font = nullptr;
    SDL_Color fg;
    SDL_Color bg;
    size_t length;
    const char* text;

public:
    BaseBoard(int x, int y, const char* fontPath, SDL_Color fg, SDL_Color bg, const char* text, size_t length);

    virtual ~BaseBoard();

    virtual void init() ;
    virtual void update();
    virtual void draw() ;
};

