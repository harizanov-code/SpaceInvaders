#include "BaseBoard.h"


BaseBoard::BaseBoard(int x, int y, const char* fontPath, SDL_Color fg, SDL_Color bg, const char* text, size_t length) : x(x), y(y), fontPath(fontPath), fg(fg), bg(bg), text(text), length(length) {
}

BaseBoard::~BaseBoard() {

	if (tex) SDL_DestroyTexture(tex);
	if (font) TTF_CloseFont(font);

}

void BaseBoard::init() {
}

void BaseBoard::update() {
}

void BaseBoard::draw() {
}
