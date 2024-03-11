// Class to replace system cursor with custom cursor for game

#pragma once

#include "Game.h"

class Mouse
{
public:

	SDL_Texture* texture;
	SDL_Rect imageRect;
	SDL_Rect collider;

	Mouse()
	{
		texture = IMG_LoadTexture(Game::renderer, "Assets/UI/Cursor_rough.png");
		imageRect.w = 25;
		imageRect.h = 25;
		collider.w = 1;
		collider.h = 1;
	}

	void Update()
	{
		SDL_GetMouseState(&imageRect.x, &imageRect.y);

	}

};