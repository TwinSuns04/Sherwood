// Mouse Component

#pragma once


#include "../Game.h"
#include "ECS.h"
#include "Components.h"
#include "SDL_mouse.h"

class Mouse : public Component
{
private:

	TransformComponent* transform;

	// vars
	int xCenter;
	int yCenter;

public:

	Mouse()
	{
		xCenter = 400;
		yCenter = 400;
	}

	Mouse(int xPos, int yPos)
	{
		xCenter = xPos;
		yCenter = yPos;
	}

	~Mouse()
	{}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		SDL_WarpMouseInWindow(Game::window, xCenter, yCenter);
		transform->position.x = xCenter;
		transform->position.y = yCenter;
	}

	void Update() override
	{
		if (Game::event.type == SDL_MOUSEMOTION)
		{
			// update player position
			transform->position.x = Game::event.motion.x;
			transform->position.y = Game::event.motion.y;



		}
	}

	
};
