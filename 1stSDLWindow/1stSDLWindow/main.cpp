#include "SDL3/SDL.h"
#include "Game.h"
#include <iostream>

Game* game = nullptr;


int main(int argc, char* argv[]) {

	const int	FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	game = new Game();
	game->init("ELDER SCROOLS", 1024,  1024, false);


	game->setState(GameState::PLAYING);
	std::cout << game->running() << std::endl;
	while (game->running()) {

		frameStart = SDL_GetTicks();

		//if (Game::gameState == MENU) {

		//}
		//else if (Game::gameState == PLAYING) {

		//}
		//else if (Game::gameState == GAME_OVER) {

		//}

		game->handleEvents();
		game->update();
		game -> render();

		frameTime = SDL_GetTicks() - frameStart;

		
		if (frameTime < frameDelay) {

			SDL_Delay(frameDelay - frameTime);
		}


	}

	game->clean();

	return 0;

}