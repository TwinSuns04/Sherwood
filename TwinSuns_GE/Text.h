// Handles display of text to render window

#pragma once

#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <string>

class Text
{
	
public:

	Text();

	Text(SDL_Renderer* renderer, const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

	void DisplayText(int xPos, int yPos, SDL_Renderer* renderer) const;

	static SDL_Texture* LoadFont(SDL_Renderer* renderer,
		const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

private:

	SDL_Texture* text_Texture = nullptr;
	mutable SDL_Rect textRect;

};
