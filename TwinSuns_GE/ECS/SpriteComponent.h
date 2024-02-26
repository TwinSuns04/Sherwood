// Responsible for drawing sprites to screen

#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureManager.h"
#include "Animation.h"
#include <map>
#include "../AssetManager.h"

class SpriteComponent : public Component
{

private:

	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;

	// variables
	bool isAnimated; // whether sprite is animated or not
	int frames; // number of frames in sprite file
	int speed = 100; // delay between frames in milliseconds

public:

	// variables
	int animIndex = 0;
	std::map<const char*, Animation> animations;

	// SDL flip allows us to know if sprite is flipped or not
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

	SpriteComponent() = default;

	// Basic Sprite
	SpriteComponent(std::string id)
	{
		SetNewTexture(id);
	}

	// Additional Constructor, dif params
	// For sprite sheets and animated sprites
	SpriteComponent(std::string id, bool isAnim)
	{
		isAnimated = isAnim;

		//Animation wompDeath = Animation(0, 6, 250);
		//animations.emplace("wompDeath", wompDeath);

		Animation canyonBackgroundAnim(0, 6, 250);
		animations.emplace("canyonAnim", canyonBackgroundAnim);
		PlayAnim("canyonAnim");


		//PlayAnim("wompDeath");

		SetNewTexture(id);

	}

	~SpriteComponent()
	{
		
	}

	void Init() override
	{
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;


		destRect.w = transform->width * transform->scale;
		destRect.h = transform->height * transform->scale;
	}

	void Update() override
	{

		// check if sprite is animated
		if (isAnimated)
		{
			// set srcRect
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks64() / speed) % frames);

		}

		srcRect.y = animIndex * transform->height;
		
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);

		// Below code included in TUT but broke mine?
		//destRect.w = transform->width * transform->scale;
		//destRect.y = transform->height * transform->scale;
	}

	void Draw() override
	{
		TextureManager::Draw(texture, srcRect, destRect, spriteFlip);
	}

	void SetNewTexture(std::string id)
	{
		texture = Game::assets->GetTexture(id);
	}

	// use to change index and frame
	void PlayAnim(const char* animName)
	{
		frames = animations[animName].frames;
		animIndex = animations[animName].index;
		speed = animations[animName].speed;
	}

};