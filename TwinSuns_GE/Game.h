// Game Loop Header

#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <list>
#include "AdvancedTimer.h"
#include "Vector2D.h"

class AssetManager;
class CollisionComponent;

class Game
{

private:
	
	// variables


	SDL_Window *window;

public:

	// variables
	static bool isRunning;

	Game();
	~Game();

	void Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen);

	// Main Functions
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
	bool Running();

	// For future AddTile future implementation
	static void AddTileFuture(int srcX, int srcy, int posX, int posY);

	// Objects
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupScenes,
		groupColliders,
	};

	// Additional Functions
	void DisplayPlayerScore(); // Display player score on screen
	void DebugOne();

};

//------------------------------------------------------------

class GameMode : public Game
{

public:

	GameMode();
	~GameMode();

	// Functions
	void TextSetter(SDL_Renderer* _renderer, const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

	SDL_Texture* LoadFont(SDL_Renderer* _renderer,
		const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

	void DisplayPlayerScoreText(int xPos, int yPos, SDL_Renderer* _renderer);

	

	// Entities
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect;

private:

	// variables
	

};
