// Game Loop Header


#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "AdvancedTimer.h"
#include "Vector2D.h"

class AssetManager;
class CollisionComponent;
class Entity;

class Game
{

private:
	
	// variables

	// Objects
	

public:

	// variables
	static bool isRunning;
	static bool collisionCheck;

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
	static SDL_Window* window;
	static SDL_Renderer *renderer;
	static SDL_Event event;
	static SDL_Rect camera;
	static AssetManager* assets;

	enum groupLabels : std::size_t
	{
		groupScenes,
		groupColliders,
		groupCharacterSprites,
		groupUI,
		groupPuzzlePieces,
	};

	// Additional Functions
	void DisplayPlayerScore(); // Display player score on screen
	void DebugOne();

};

//------------------------------------------------------------

// Game Story is broken up into 10 parts, each with its own scenes

class GameMode : public Game
{

public:

	GameMode();
	~GameMode();

// Member Functions
#pragma region Functions

	void SetStoryPart(int part);
	int GetStoryPart();
	void ManageStoryPart(int part, std::string scene);

	void SetStoryPartScene(std::string scene);
	std::string GetStoryPartScene();

	bool PuzzleCollisionCheck();
	void PuzzlePieceInteraction();

	// Canyon Run functions used to display player score to screen
	// Maybe utilize for dialogue?
	/*
	void TextSetter(SDL_Renderer* _renderer, const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

	SDL_Texture* LoadFont(SDL_Renderer* _renderer,
		const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

	void DisplayPlayerScoreText(int xPos, int yPos, SDL_Renderer* _renderer);
	*/

#pragma endregion Functions

	
	// Objects
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect;

	

private:

	// variables
	Entity* clickedPuzzlePiece;
	
	int storyPart;
	int storyPartOld;
	int storyPartNew;
	std::string storyScene;
	std::string storySceneOld;
	std::string storySceneNew;

};
