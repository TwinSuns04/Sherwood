#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{

private:

public:

	Vector2D position;
	Vector2D velocity;
	int speed = 4;

	int height = 32;
	int width = 32;
	int scale = 1;

	TransformComponent()
	{
		position.Zero();
	}

	TransformComponent(int sc)
	{
		position.Zero();
		scale = sc;
	}

	TransformComponent(float x, float y)
	{
		position.x = x;
		position.y = y;
	}

	TransformComponent(float x, float y, int w, int h, int sc)
	{
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	void Init() override
	{
		velocity.Zero();
	}

	// override Component class Update() function
	void Update() override
	{
		// Create movement based off input
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}

	bool SetNewTransformPos(float x, float y)
	{
		position.x = x;
		position.y = y;

		if ((position.x == x) && (position.y == y))
		{
			return true;
		}
		else 
		{
			return false;
		}
		
	}

};