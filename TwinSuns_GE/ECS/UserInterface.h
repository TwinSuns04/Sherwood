#pragma once

#include "ECS.h"
#include "../AssetManager.h"
#include "../Game.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class UserInterface : public Component
{
public:

	UserInterface(int xPos, int yPos, std::string text, std::string font, SDL_Color& color) :
		uiText(text), uiFont(font), uiTextColor(color)
	{
		position.x = xPos;
		position.y = yPos;

		SetUIText(uiText, uiFont);
	}

	~UserInterface()
	{

	}

	void SetUIText(std::string text, std::string font)
	{
		// Create a surface
		SDL_Surface* surf = TTF_RenderText_Blended(Game::assets->GetFont(font), text.c_str(), uiTextColor);

		// Create a render of surface
		uiTexture = SDL_CreateTextureFromSurface(Game::renderer, surf);
		SDL_FreeSurface(surf);

		// Get width and height of created text
		SDL_QueryTexture(uiTexture, nullptr, nullptr, &position.w, &position.h);
	}

	void Draw() override
	{
		SDL_RenderCopy(Game::renderer, uiTexture, nullptr, &position);
	}

private:

	SDL_Rect position;
	std::string uiText;
	std::string uiFont;
	SDL_Color uiTextColor;
	SDL_Texture* uiTexture;
};