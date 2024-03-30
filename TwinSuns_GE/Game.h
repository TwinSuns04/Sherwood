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
	void DisplayText();
	void DebugOne();

};

//------------------------------------------------------------

// Game Story is broken up into 10 parts, each with its own scenes

class GameMode : public Game
{

public:

	GameMode();
	~GameMode();

	void TextSetter(SDL_Renderer* _renderer, const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

	SDL_Texture* LoadFont(SDL_Renderer* _renderer,
		const std::string& fontPath, int fontSize,
		const std::string& messageText, const SDL_Color& color);

	void DisplayOnScreenText(int xPos, int yPos, SDL_Renderer* _renderer);


	// Member Functions
	void SetStoryPart(int part);
	int GetStoryPart();
	void ManageStoryPart(int part, char scene);

	void SetStoryScene(char scene);
	char GetStoryScene();
	void UpdateBackgroundScene(std::string sceneID);

	bool PuzzleCollisionCheck();
	void PuzzlePieceInteraction();

	// Functions to update vars to correspond with story parts and scenes
#pragma region LoadFunctions
	void PrologueSceneB();

	void Part1SceneA();
	void Part1SceneB();
	void Part1SceneC();
	void Part1SceneD();
	void Part1SceneE();

	void Part2SceneA();
	void Part2SceneB();
	void Part2SceneC();

	void Part3SceneA();

	void Part4SceneA();
	void Part4SceneB();

	void Part5SceneA();

	void Part6SceneA();
	void Part6SceneB();

	void Part7SceneA();
	void Part7SceneB();

	void Part8SceneA();
	void Part8SceneB();

	void Part9SceneA();

	void GameComplete();
#pragma endregion LoadFunctions

	// Canyon Run functions used to display player score to screen
	// Maybe utilize for dialogue?
	
	// Objects
	SDL_Texture* textTexture = nullptr;
	SDL_Rect textRect;

private:

	// variables and objects
	Entity* clickedPuzzlePiece;
	
	static int storyPart;
	int storyPartOld;
	int storyPartNew;
	static char storyScene;

};
