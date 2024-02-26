#pragma once

#include <string>
#include "SDL.h"
#include "Components.h"
#include "../TextureManager.h"

class CollisionComponent : public Component
{

public:

	SDL_Rect collider;
	std::string tag;

	SDL_Texture* tex;
	SDL_Rect srcRect, destRect;

	TransformComponent* transform;

	CollisionComponent(std::string t)
	{
		tag = t;
	}


	CollisionComponent(std::string t, int xPos, int yPos, int size)
	{
		tag = t;
		collider.x = xPos;
		collider.y = yPos;
		collider.w = collider.h = size;
	}

	void Init() override
	{
		

		// check if entity(object/actor) has component already
		if (!entity->hasComponent<TransformComponent>())
		{
			entity->addComponent<TransformComponent>();

		}

		transform = &entity->getComponent<TransformComponent>();
		
		tex = TextureManager::LoadTexture("Assets/ColText.png");

		
		srcRect = { 0, 0, 32, 32 };
		destRect = { collider.x, collider.y, collider.w, collider.h };

	}

	void Draw() override
	{
		TextureManager::Draw(tex, srcRect, destRect, SDL_FLIP_NONE);
	}

	void Update() override
	{
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
				
	}

};
