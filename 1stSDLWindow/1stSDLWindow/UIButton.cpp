#include "UIButton.h"
#include "TextureManager.h"
#include <iostream>

UIButton::UIButton(int x, int y, const char* fontPath, int fontSize,
    const std::string& label, SDL_Color fg, SDL_Color bg,
    std::function<void()> onClick)
    : x(x), y(y), fontPath(fontPath), fontSize(fontSize),
    label(label), fg(fg), bg(bg), onClick(onClick) {
    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init failed: " << SDL_GetError() << std::endl;
        return;
    }

    font = TTF_OpenFont(fontPath, fontSize);
    if (!font) {
        std::cerr << "Failed to load font: " << SDL_GetError() << std::endl;
        // Optionally try a smaller size or fallback here
        return;
    }

    createTexture();
}

UIButton::~UIButton() {
    clean();
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

void UIButton::createTexture() {
    if (tex) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
    // Use your TextureManager to load the texture from text
    tex = TextureManager::LoadTextTexture(font, label.c_str(), label.size(), fg, bg);
    if (!tex) {
        std::cerr << "Failed to create button texture\n";
    }
}

void UIButton::draw() {
    if (!tex) return;

    float textW, textH;
    SDL_GetTextureSize(tex, &textW, &textH);

    SDL_FRect srcRect = { 0, 0, textW, textH };
    SDL_FRect destRect = { static_cast<float>(x), static_cast<float>(y), textW, textH };

    TextureManager::Draw(tex, srcRect, destRect);
}

void UIButton::handleEvent(const SDL_Event& e) {
    if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button == SDL_BUTTON_LEFT) {
        int mx = e.button.x;
        int my = e.button.y;

        float textW, textH;
        SDL_GetTextureSize(tex, &textW, &textH);
        std::cout << "I am handling even here";
        if (mx >= x && mx <= x + textW && my >= y && my <= y + textH) {
            if (onClick) onClick();
        }
    }
}

void UIButton::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}

void UIButton::setLabel(const std::string& newLabel) {
    label = newLabel;
    createTexture();
}

void UIButton::clean() {
    if (tex) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
}
