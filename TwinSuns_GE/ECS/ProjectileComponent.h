#pragma once

#include "ECS.h"
#include "Components.h"
#include "..\Vector2D.h"

class ProjectileComponent : public Component
{

public:

	ProjectileComponent(int rng, int spd, Vector2D crosshairPos) : range(rng), speed(spd),  playerPos(crosshairPos)
	{
		
	}

	~ProjectileComponent()
	{

	}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity = projectileDelta;

	}

	void Update() override
	{
		//std::cout << "Distance: " << distance << std::endl;
		distance += speed;

		/*
		if (distance >= range)
		{
			std::cout << "Destroy Projectile" << std::endl;
			entity->Destroy();
			std::cout << "Entity: " << entity << std::endl;
		}
		else if ((transform->position.x > 640) ||
			(transform->position.x < 0) ||
			(transform->position.y > 640) || 
			(transform->position.y < 0))
		{
			std::cout << "Projectile is out of bounds" << std::endl;
			entity->Destroy();
			std::cout << "Entity: " << entity << std::endl;
		}
		*/
		
	}

	// Calculate travel vector of laser based on player position
	void CalcTrajectory(Vector2D target)
	{
		// calc slope, rise/run
		switch (projectileNum)
		{
		case 0:
			projectileStart = laserRightPos;
			break;

		case 1:
			projectileStart = laserLeftPos;
			break;

		default:
			break;
		}

		projectileDelta = Vector2D(1, -2);

	}

private:

	TransformComponent* transform;
	SpriteComponent* sprite;

	int range = 0;
	int speed = 0;
	int distance = 0;
	int projectileNum = 0;
	Vector2D projectileStart = Vector2D(0, 0);
	Vector2D playerPos = Vector2D(0, 0);
	Vector2D projectileDelta = Vector2D(0, -2);

	const Vector2D laserLeftPos = Vector2D(48, 480);
	const Vector2D laserRightPos = Vector2D(568, 480);

};
