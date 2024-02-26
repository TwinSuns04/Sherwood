// Use to draw game background / map
// 

#pragma once

#include "Components.h"
#include "SDL.h"

class TileComponent : public Component
{
	
public:

	TransformComponent* transform;
	SpriteComponent* sprite;
	SDL_Rect tileRect;

	int tileID;
	const char* path;

	TileComponent() = default;
	
	TileComponent(int x, int y, int w, int h, int id)
	{
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;

		switch (tileID)
		{
		case 1:
			path = "Assets/colText.png";
			break;

		case 2:
			path = "Assets/sky.png";
			break;

		case 3:
			path = "Assets/canyonWall2.png";
			break;

		default:
			break;
		}

	}

	void Init() override
	{
		entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<TransformComponent>();
		
		entity->addComponent<SpriteComponent>(path);
		sprite = &entity->getComponent<SpriteComponent>();


	}

	/*
	
	*/
	// eventually replace Init() override
	void InitFuture()
	{

	}

};
