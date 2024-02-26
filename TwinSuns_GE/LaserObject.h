#pragma once
#include "Game.h"
#include "TextureManager.h"
#include "Vector2D.h"

class LaserObject
{
public:

	LaserObject();
	LaserObject(const char* texture, SDL_Renderer* ren); // tutorial
	~LaserObject();

	void Update();
	void Render();

	void SetNewTexture(const char* texture);
	void SetLaserTransform(Vector2D pos, Vector2D vel);
	Vector2D GetLaserPos();
	Vector2D GetLaserVel();
	bool GetActiveStatus();
	
protected:

	bool activeStatus;

private:

	SDL_Renderer* renderer;
	SDL_Texture* objTexture;
	SDL_Rect srcRect, destRect;
	Vector2D laserPos;
	Vector2D laserVel;

};
