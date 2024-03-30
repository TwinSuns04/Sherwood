// TwinSuns 2D - Game Engine

// Robin Hood Point and Click Adventure
// Based on the novel 'The Merry Adventures of Robin Hood' by Howard Pyle

#include "SDL.h"
#include <iostream>
#include "Game.h"

// create Game instance

Game* game = nullptr;

int main(int argc, char* args[])
{
	(void)argc;
	(void)args;

	const int FPS = 30;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();

	game->Init("TwinSuns Game Engine - RobinHoodPnC", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1600, 1000, false);

	while (game->Running())
	{
		frameStart = SDL_GetTicks64();

		game->HandleEvents();
		game->Update();
		game->Render();
		//game->DisplayPlayerScore();

		frameTime = SDL_GetTicks64() - frameStart;

		// cap FPS
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->Clean();


	return 0;
}