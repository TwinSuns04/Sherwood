#pragma once

#include "Game.h"

class GameObject
{

public:

	// Constructor and destructor
	GameObject(const char* textureSheet, int x, int y);
	~GameObject();

	// Functions
	void Update();
	void Render();

private:

	int xPos;
	int yPos;

	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRec;

protected:

};

