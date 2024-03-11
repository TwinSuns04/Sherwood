#include "Game.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "TextureMap.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "AssetManager.h"
#include "PuzzleSystem.h"
#include <sstream>

TextureMap* map;
Manager manager;
GameMode* gameMode = nullptr;
AdvancedTimer* timerEnemy;

// Puzzle Systems
PuzzleSystem* puzzleSysZero;
PuzzleSystem* puzzleSysOne;

SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

SDL_Rect Game::camera = { 0, 0, 640, 640 };

bool Game::isRunning = false;
bool Game::collisionCheck = false;

// Create and add entities
// Some may need to be moved after prototype
auto& player(manager.AddEntity());
auto& backgroundScene(manager.AddEntity()); // Control the 'scene' of the game
auto& basicUI(manager.AddEntity()); // Test UI
auto& robinHood(manager.AddEntity()); // Robin Hood Character
auto& rangerPrologue(manager.AddEntity()); // Ranger for prologue


Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(const char* title, int xPos, int yPos, int width, int height, bool fullscreen)
{

	gameMode = new GameMode();
	timerEnemy = new AdvancedTimer();

	// Puzzle Instances
	puzzleSysZero = new PuzzleSystem();
	puzzleSysOne = new PuzzleSystem();

	if (timerEnemy->GetIsStarted() == false)
	{
		timerEnemy->TimerStart();
	}

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initializing SDL and relevancies
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		// check if window created
		if (window)
		{
			std::cout << "Window Created" << std::endl;

			SDL_SetWindowMouseGrab(window, SDL_TRUE);

			if (SDL_GetWindowMouseGrab(window))
			{
				std::cout << "Window grabbed" << std::endl;
			}
			else
			{
				std::cout << "Window NOT grabbed" << std::endl;

			}
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 71, 135, 120, 255);

			std::cout << "Renderer Created" << std::endl;

		}

		isRunning = true;
	}
	else
	{
		// occurs if SDL is not init properly
		isRunning = false;
	}

	// initialize SDL_ttf check
	if (TTF_Init() == -1)
	{
		std::cout << "SDL ttf failed to initialize" << std::endl;
		// occurs if SDL is not init properly
		isRunning = false;
	}

	// Add fonts to asset manager/ font library
	assets->AddFont("Arial", "Assets/arial.ttf", 16);

	// Add textures to asset manager / texture library
#pragma region TextureLibrary

	// Scenes
	assets->AddTexture("PrologueScene", "Assets/Scenes/RobinAndTheRangerv001.png");
	assets->AddTexture("Start", "Assets/Scenes/KirkleyHall_ref.png");

	// Characters
	assets->AddTexture("RobinSprite", "Assets/Characters/Robin_rough.png");
	assets->AddTexture("RangerSprite", "Assets/Characters/Ranger_rough.png");

	// User Interface
	assets->AddTexture("Cursor", "Assets/UI/Cursor_rough.png");

	// Puzzle Pieces
	assets->AddTexture("ArrowQuiver", "Assets/PuzzleComp/Quiver_rough.png");
	assets->AddTexture("DeerHeart", "Assets/PuzzleComp/DeerHeart_rough.png");


#pragma endregion TextureLibrary

	map = new TextureMap();

	// Load Map
	//TextureMap::LoadTextureMap("Assets/CanyonRun16x16.map", 16, 16);

// Create Puzzle Systems and set values using structs
// Maybe read values from external file????
#pragma region PuzzleSystemsCreation

	// Prologue Puzzle System
#pragma region PrologueSystem

	puzzleSysZero->puzzlePieceOne.puzzleID = "ArrowQuiver";
	puzzleSysZero->puzzlePieceOne.storyPart = 0;
	puzzleSysZero->puzzlePieceOne.storyScene = "Prologue";
	puzzleSysZero->puzzlePieceOne.transform = std::vector<int>{ 500, 600, 200, 200, 1 };
	puzzleSysZero->puzzlePieceOne.dependencies = {};

	puzzleSysZero->puzzlePieceTwo.puzzleID = "DeerHeart";
	puzzleSysZero->puzzlePieceTwo.storyPart = 0;
	puzzleSysZero->puzzlePieceTwo.storyScene = "Prologue";
	puzzleSysZero->puzzlePieceTwo.transform = std::vector<int>{ 1250, 600, 50, 50, 1 };
	puzzleSysZero->puzzlePieceTwo.dependencies = { "ArrowQuiver" };

#pragma endregion PrologueSystem

	puzzleSysZero->CreateEntities();

#pragma endregion PuzzleSystemsCreation

	// Create Objects and add their components
#pragma region ComponentCreation

	// Player object
	player.addComponent<TransformComponent>(0.0f, 0.0f, 1, 1, 1);
	player.addComponent<CollisionComponent>("MouseCursor");
	player.addComponent<KeyboardController>();
	player.addComponent<Mouse>(800, 500);
	

	// Background Scene Object
	backgroundScene.addComponent<TransformComponent>(0.0f, 0.0f, 1600, 1000, 1);
	backgroundScene.addComponent<SpriteComponent>("PrologueScene");
	backgroundScene.AddGroup(groupScenes);

	// Character Objects
	robinHood.addComponent<TransformComponent>(800.0f, 400.0f, 400, 400, 1);
	robinHood.addComponent<SpriteComponent>("RobinSprite");
	robinHood.AddGroup(groupCharacterSprites);

	rangerPrologue.addComponent<TransformComponent>(200.0f, 400.0f, 400, 400, 1);
	rangerPrologue.addComponent<SpriteComponent>("RangerSprite");
	rangerPrologue.AddGroup(groupCharacterSprites);

	// User Interface Objects
	SDL_Color white = { 255, 255, 255, 255 };
	basicUI.addComponent<UserInterface>(400, 400, "Test", "Arial", white);

#pragma endregion ComponentCreation
	
}

// Create lists of group objects, using AssetManager Class,
// by getting all objects with desired 'label'
auto& scenes(manager.GetGroup(Game::groupScenes));
auto& characterSprites(manager.GetGroup(Game::groupCharacterSprites));
auto& puzzlePieces(manager.GetGroup(Game::groupPuzzlePieces));
auto& userInterface(manager.GetGroup(Game::groupUI));

// Handle SDL events
void Game::HandleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;

	}	
	
}

void Game::Update()
{
	// UI string update, not in use
	/*
	std::stringstream ss;
	ss << "Test Output";
	basicUI.getComponent<UserInterface>().SetUIText(ss.str(), "arial");
	*/

	manager.Refresh();
	manager.Update();
	

	// Check which storyPart is active

	// camera code, not in use
	/*
	camera.x = skyHop.getComponent<TransformComponent>().position.x - 320;
	camera.y = skyHop.getComponent<TransformComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.y > camera.h)
		camera.y = camera.h;
		*/

}


void Game::Render()
{
	SDL_RenderClear(renderer);

	// Using painters algorithm, items on screen go back to front, draw UI last
	for (auto& s : scenes)
	{
		s->Draw();
	}

	for (auto& c : characterSprites)
	{
		c->Draw();
	}

	for (auto& p : puzzlePieces)
	{
		p->Draw();
	}

	for (auto& i : userInterface)
	{
		i->Draw();
	}
	
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_SetWindowMouseGrab(window, SDL_FALSE);
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();

	std::cout << "Game Cleaned" << std::endl;
}

bool Game::Running()
{
	return isRunning;
}

void Game::DisplayPlayerScore()
{
	/*
	std::string scoreString = "Score: ";
	std::string scoreString2 = std::to_string(gameMode->GetPlayerScore());
	scoreString.append(scoreString2);

	gameMode->TextSetter(renderer, "Assets/arial.ttf", 24, scoreString, { 255, 0, 0, 255 });

	gameMode->DisplayPlayerScoreText(20, 20, renderer);
	*/
}

void Game::DebugOne()
{
	std::cout << "DebugOne()" << std::endl;
	std::cout << "ArrowQuiver.bUsed: " <<
		assets->GetPuzzlePiece("ArrowQuiver")->getComponent<PuzzlePieceComponent>().GetbUsed()
		<< std::endl;
}

void Game::AddTileFuture(int srcX, int srcY, int posX, int posY)
{
	/*
	auto& tile(manager.AddEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.AddGroup(groupMap);
	*/
}

//----------------------------------------------------------
// Start GameMode class

GameMode::GameMode()
{
	// init vars
	GameMode::storyPart = 0;
	GameMode::storyScene = "PrologueScene";

	clickedPuzzlePiece = nullptr;

}

GameMode::~GameMode()
{

}

bool GameMode::PuzzleCollisionCheck()
{
	SDL_Rect playerCollider = player.getComponent<CollisionComponent>().collider;

	for (auto& p : puzzlePieces)
	{
		std::cout << "PuzzlePiece id: " << p->getComponent<PuzzlePieceComponent>().pieceName
			<< std::endl;

		SDL_Rect tempCol = p->getComponent<CollisionComponent>().collider;

		if (Collision::AABB(playerCollider, tempCol))
		{

			std::cout << "Player x PuzzlePiece collision" << std::endl;
			clickedPuzzlePiece = p;

			return true;
		}
		else
		{
			std::cout << "No Player x PuzzlePiece collision" << std::endl;
			clickedPuzzlePiece = nullptr;

			continue;
		}
	}

	return false;
}

void GameMode::PuzzlePieceInteraction()
{
	clickedPuzzlePiece->getComponent<PuzzlePieceComponent>().SetClickStatus(true);
}

// Functions used in CanyonRun to display player score to screen
// Not in use
/*
void GameMode::TextSetter(SDL_Renderer* _renderer, const std::string& fPath,
	int fSize, const std::string& message, const SDL_Color& color)
{
	

	textTexture = LoadFont(_renderer, fPath, fSize, message, color);

	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);

}

SDL_Texture* GameMode::LoadFont(SDL_Renderer* _renderer,
	const std::string& fontPath, int fontSize,
	const std::string& messageText, const SDL_Color& color)
{
	TTF_Font* fontGM = TTF_OpenFont(fontPath.c_str(), fontSize);

	if (!fontGM)
	{
		std::cout << "Failed to load font" << std::endl;
	}

	auto textSurface = TTF_RenderText_Solid(fontGM, messageText.c_str(), color);

	if (!textSurface)
	{
		std::cout << "Failed to load textSurface" << std::endl;
	}

	auto textTexture = SDL_CreateTextureFromSurface(_renderer, textSurface);

	if (!textTexture)
	{
		std::cout << "Failed to load textTexture" << std::endl;
	}

	SDL_FreeSurface(textSurface);

	return textTexture;
}

void GameMode::DisplayPlayerScoreText(int xPos, int yPos, SDL_Renderer* _renderer)
{
	textRect.x = xPos;
	textRect.y = yPos;
	SDL_RenderCopy(_renderer, textTexture, nullptr, &textRect);
}
*/
