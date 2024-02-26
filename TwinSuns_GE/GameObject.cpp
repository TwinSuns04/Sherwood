// Not in use
// Functionality has been moved to ECS class

#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(textureSheet);

	xPos = x;
	yPos = y;
}

GameObject::~GameObject()
{

}

void GameObject::Update()
{
	xPos++;
	yPos++;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRec.x = xPos;
	destRec.y = yPos;
	destRec.w = srcRect.w * 2;
	destRec.h = srcRect.h * 2;

}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRec);
}
