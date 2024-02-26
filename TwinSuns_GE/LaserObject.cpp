#include "LaserObject.h"

LaserObject::LaserObject()
{
}

LaserObject::LaserObject(const char* texture, SDL_Renderer* ren)
{
	// Tutorial
	renderer = ren;
	objTexture = TextureManager::LoadTexture(texture);
	activeStatus = true;
}

LaserObject::~LaserObject()
{
}

void LaserObject::Update()
{
	// Tutorial
	laserPos.x = 200;
	laserPos.y = 200;

	srcRect.h = 32;
	srcRect.w = 32;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = laserPos.x;
	destRect.y = laserPos.y;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void LaserObject::Render()
{
	// Tutorial
	SDL_RenderCopy(renderer, objTexture, &srcRect, &destRect);
}

void LaserObject::SetNewTexture(const char* texture)
{
	objTexture = TextureManager::LoadTexture(texture);
}

void LaserObject::SetLaserTransform(Vector2D pos, Vector2D vel)
{
	laserPos = pos;
	laserVel = vel;
}

Vector2D LaserObject::GetLaserPos()
{
	return laserPos;
}

Vector2D LaserObject::GetLaserVel()
{
	return laserVel;
}

bool LaserObject::GetActiveStatus()
{
	return activeStatus;
}
