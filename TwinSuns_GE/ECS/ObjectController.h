// Controller for objects other than players

#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class ObjectController : public Component
{

public:

	TransformComponent* transform;
	SpriteComponent* sprite;



	// variables
	int speed;

	ObjectController();

	ObjectController(int mSpeed)
	{
		speed = mSpeed;
	}

	ObjectController(TransformComponent* mTransform, SpriteComponent* mSprite, int mSpeed)
	{
		transform = mTransform;
		sprite = mSprite;
		speed = mSpeed;
	}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

	}

	void Update() override
	{
		MoveObject();
		

	}
	
	void MoveObject()
	{
		
	}

};