#include "Game.h"
#include "SDL_ttf.h"
#include "TextureManager.h"
#include "TextureMap.h"
#include "ECS/Components.h"
#include "Collision.h"
#include "AssetManager.h"

TextureMap* map;
Manager manager;
GameMode* gameMode = nullptr;
AdvancedTimer* timerEnemy;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

SDL_Rect Game::camera = { 0, 0, 640, 640 };

bool Game::isRunning = false;

// Create and add entities


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

	if (timerEnemy->GetIsStarted() == false)
	{
		timerEnemy->TimerStart();
	}

	int flags = 0;

	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	// initializing SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised" << std::endl;

		window = SDL_CreateWindow(title, xPos, yPos, width, height, flags);

		// check if window created
		if (window)
		{
			std::cout << "Window Created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);

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

	// Add textures to asset manager / texture library
	//assets->AddTexture("collision border", "Assets/collisionBorder.png");

	map = new TextureMap();

	// Load Map
	//TextureMap::LoadTextureMap("Assets/CanyonRun16x16.map", 16, 16);
	
	
}

// create lists of group objects

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


	manager.Refresh();
	manager.Update();

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

	// using painters algorithm, items on screen go back to front
	
	
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
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
	

}

GameMode::~GameMode()
{

}

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

