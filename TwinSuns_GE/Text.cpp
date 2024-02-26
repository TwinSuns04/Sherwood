#include "Text.h"
#include "Game.h"

Text::Text()
{

}

Text::Text(SDL_Renderer* renderer, const std::string& fontPath, int fontSize,
	const std::string& messageText, const SDL_Color& color)
{
	text_Texture = LoadFont(renderer, fontPath, fontSize, messageText, color);

	SDL_QueryTexture(text_Texture, nullptr, nullptr, &textRect.w, &textRect.h);
}

void Text::DisplayText(int xPos, int yPos, SDL_Renderer* renderer) const
{
	textRect.x = xPos;
	textRect.y = yPos;
	SDL_RenderCopy(renderer, text_Texture, nullptr, &textRect);

}

SDL_Texture *Text::LoadFont(SDL_Renderer* renderer, const std::string& fontPath, int fontSize,
	const std::string& messageText, const SDL_Color& color)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

	// error check
	if (!font)
	{
		std::cout << "Failed to load font texture" << std::endl;
	}

	auto text_Surface = TTF_RenderText_Solid(font, messageText.c_str(), color);

	// error check
	if (!text_Surface)
	{
		std::cout << "Failed to create text surface" << std::endl;
	}

	// make the texture
	auto text_Texture = SDL_CreateTextureFromSurface(renderer, text_Surface);

	if (!text_Texture)
	{
		std::cout << "Failed to create text texture" << std::endl;
	}

	SDL_FreeSurface(text_Surface);

	return text_Texture;

}
