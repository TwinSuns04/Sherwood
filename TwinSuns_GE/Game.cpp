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
#pragma region PuzzleSystemInits
PuzzleSystem* puzzleSysZero; // For Prologue story Scene A
PuzzleSystem* puzzleSysZeroB; // For prologue story Scene B

PuzzleSystem* puzzleSysOneA; // For Part I Scene A
PuzzleSystem* puzzleSysOneB; // For Part I Scene B
PuzzleSystem* puzzleSysOneC; // For Part I Scene C
PuzzleSystem* puzzleSysOneD; // For Part I Scene D
PuzzleSystem* puzzleSysOneE; // For Part I Scene E

PuzzleSystem* puzzleSysTwoA; // For Part II Scene A
PuzzleSystem* puzzleSysTwoB; // For Part II Scene B
PuzzleSystem* puzzleSysTwoC; // For Part II Scene C

PuzzleSystem* puzzleSysThreeA; // For Part III Scene A

PuzzleSystem* puzzleSysFourA; // For Part IV Scene A
PuzzleSystem* puzzleSysFourB; // For Part IV Scene B

PuzzleSystem* puzzleSysFiveA; // For Part V Scene A

PuzzleSystem* puzzleSysSixA; // For Part VI Scene A
PuzzleSystem* puzzleSysSixB; // For Part VI Scene B


PuzzleSystem* puzzleSysSevenA; // For Part VII Scene A
PuzzleSystem* puzzleSysSevenB; // For Part VII Scene B

PuzzleSystem* puzzleSysEightA; // For Part VIII Scene A
PuzzleSystem* puzzleSysEightB; // For Part VIII Scene B

PuzzleSystem* puzzleSysNineA; // For Part IX Scene A
#pragma endregion PuzzleSystemInits

// Graphics and input
SDL_Window* Game::window = nullptr;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

// Camera not in use
SDL_Rect Game::camera = { 0, 0, 640, 640 };

bool Game::isRunning = false;
bool Game::collisionCheck = false;

// Create and add entities
// Some may need to be moved after prototype
auto& player(manager.AddEntity());
auto& backgroundScene(manager.AddEntity()); // Control the 'scene' of the game
auto& basicUI(manager.AddEntity()); // Test UI
auto& robinHood(manager.AddEntity()); // Robin Hood Character
auto& littleJohn(manager.AddEntity()); // Little John Character
auto& sheriff(manager.AddEntity()); // The Sheriff Character
auto& npcOne(manager.AddEntity()); // Character that is altered to match story/scene
auto& npcTwo(manager.AddEntity()); // Character that is altered to match story/scene
auto& npcThree(manager.AddEntity()); // Character that is altered to match story/scene


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

	// PuzzleSystem Instances
	puzzleSysZero = new PuzzleSystem(0, 'A');
	puzzleSysZeroB = new PuzzleSystem(0, 'B');

	puzzleSysOneA = new PuzzleSystem(1, 'A');
	puzzleSysOneB = new PuzzleSystem(1, 'B');
	puzzleSysOneC = new PuzzleSystem(1, 'C');
	puzzleSysOneD = new PuzzleSystem(1, 'D');
	puzzleSysOneE = new PuzzleSystem(1, 'E');

	puzzleSysTwoA = new PuzzleSystem(2, 'A');
	puzzleSysTwoB = new PuzzleSystem(2, 'B');
	puzzleSysTwoC = new PuzzleSystem(2, 'C');

	puzzleSysThreeA = new PuzzleSystem(3, 'A');

	puzzleSysFourA = new PuzzleSystem(4, 'A');
	puzzleSysFourB = new PuzzleSystem(4, 'B');
	
	puzzleSysFiveA = new PuzzleSystem(5, 'A');

	puzzleSysSixA = new PuzzleSystem(6, 'A');
	puzzleSysSixB = new PuzzleSystem(6, 'B');

	puzzleSysSevenA = new PuzzleSystem(7, 'A');
	puzzleSysSevenB = new PuzzleSystem(7, 'B');

	puzzleSysEightA = new PuzzleSystem(8, 'A');
	puzzleSysEightB = new PuzzleSystem(8, 'B');

	puzzleSysNineA = new PuzzleSystem(9, 'A');

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

			std::cout << "Renderer Created\n\n\n\n" << std::endl;

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
	assets->AddTexture("Start", "Assets/Scenes/KirkleyHall_ref.png");
	assets->AddTexture("PrologueScene", "Assets/Scenes/RobinAndTheRangerv001.png"); // 0A
	assets->AddTexture("RobinFightsLJ", "Assets/Scenes/RobinAndLittleJohn_v001.png"); // 0B

	assets->AddTexture("SherwoodForest1", "Assets/Scenes/SherwoodForest1_v001.png"); // 1A
	assets->AddTexture("BlueBoarInt", "Assets/Scenes/BlueBoarInt_v001.png"); // 1B
	assets->AddTexture("SherwoodForest2", "Assets/Scenes/SherwoodForest2_v001.png"); // 1C
	assets->AddTexture("ArcheryComp", "Assets/Scenes/ArcheryComp2_v001.png"); // 1D
	assets->AddTexture("HangmansNoose", "Assets/Scenes/HangmansNoose_v001.png"); // 1E

	assets->AddTexture("SherwoodForest3", "Assets/Scenes/SherwoodForest3_v001.png"); // 2A
	assets->AddTexture("NottinghamSquare", "Assets/Scenes/NottinghamTownCenter_v001.png"); // 2B
	assets->AddTexture("RobinsCamp", "Assets/Scenes/RobinsCamp_v001.png"); // 2C

	assets->AddTexture("SherwoodForestRoad", "Assets/Scenes/SherwoodForestRoad_v001.png"); // 3A

	assets->AddTexture("BlueBoar", "Assets/Scenes/BlueBoar_v001.png");
	assets->AddTexture("NottinghamChurch", "Assets/Scenes/NottinghamChurch2_v001.png");
	assets->AddTexture("NottinghamOuter", "Assets/Scenes/NottinghamTown_Outer.png");
	assets->AddTexture("RoadToNottingham2", "Assets/Scenes/RoadToNottingham2_v001.png");
	

	
	assets->AddTexture("SherwoodForestB1", "Assets/Scenes/SherwoodForestBalladOne_v001.png");
	
	assets->AddTexture("TheWedding", "Assets/Scenes/TheWedding_v001.png");


	// Characters
	assets->AddTexture("RobinSprite", "Assets/Characters/Robin_rough.png"); // RobinHood w/ bow
	assets->AddTexture("RobinSpriteQS", "Assets/Characters/RobinQS_rough.png");
	assets->AddTexture("LittleJohnQS", "Assets/Characters/LittleJohnQS_rough.png");
	assets->AddTexture("TheSheriff", "Assets/Characters/TheSheriff_rough.png");
	assets->AddTexture("RangerSprite", "Assets/Characters/Ranger_rough.png");
	assets->AddTexture("TheTinker", "Assets/Characters/TheTinker_rough.png");
	assets->AddTexture("Stutley", "Assets/Characters/Stutley_rough.png");
	assets->AddTexture("Scarlet", "Assets/Characters/Scarlet_rough.png");
	assets->AddTexture("Butcher", "Assets/Characters/Butcher_rough.png");
	assets->AddTexture("PeasantOne", "Assets/Characters/Peasant1_rough.png");
	assets->AddTexture("PeasantTwo", "Assets/Characters/Peasant2_rough.png");
	assets->AddTexture("PeasantThree", "Assets/Characters/Peasant3_rough.png");

	// Puzzle Pieces, mostly in order of appearance, some are reused
	assets->AddTexture("ArrowQuiver", "Assets/PuzzleComp/Quiver.png"); // 0A
	assets->AddTexture("DeerHeart", "Assets/PuzzleComp/DeerHeart.png"); // 0A
	assets->AddTexture("QuarterStaff", "Assets/PuzzleComp/QuarterStaff.png"); // 0B, 1C, 3A
	assets->AddTexture("Horn", "Assets/PuzzleComp/WarHorn.png"); // 0B, 1C
	assets->AddTexture("CoinPurse", "Assets/PuzzleComp/CoinPurse.png"); // 1B, 2C
	assets->AddTexture("Tankard_Empty", "Assets/PuzzleComp/Tankard_Empty.png"); // 1B
	assets->AddTexture("BrokenQS", "Assets/PuzzleComp/BrokenStaff.png"); // 1C
	assets->AddTexture("Arrow", "Assets/PuzzleComp/Arrow.png"); // 1D
	assets->AddTexture("Arrow_FlipH", "Assets/PuzzleComp/Arrow_FlipH.png"); // 1D
	assets->AddTexture("Cloak_Blue", "Assets/PuzzleComp/Cloak_Blue.png"); // 1E
	assets->AddTexture("Cloak_Brown", "Assets/PuzzleComp/Cloak_Brown.png"); // 1E
	assets->AddTexture("PorkRibs", "Assets/PuzzleComp/PorkRibs.png"); // 2B
	assets->AddTexture("Steak", "Assets/PuzzleComp/Steak.png"); // 2B
	assets->AddTexture("TurkeyLeg", "Assets/PuzzleComp/TurkeyLeg.png"); // 2B, 2C
	assets->AddTexture("Coin_Stack", "Assets/PuzzleComp/Coin_Stack.png"); // 2B
	assets->AddTexture("Wine", "Assets/PuzzleComp/Wine.png"); // 2C
	assets->AddTexture("Shirt_BlueGray", "Assets/PuzzleComp/Shirt_BlueGray.png"); // 4B
	assets->AddTexture("Hat_Red", "Assets/PuzzleComp/Hat_Red.png"); // 4B
	assets->AddTexture("Harp", "Assets/PuzzleComp/Harp.png"); // 4B


	assets->AddTexture("Cloud", "Assets/PuzzleComp/Cloud.png");
	assets->AddTexture("Tankard_Full", "Assets/PuzzleComp/Tankard_Full.png");
	assets->AddTexture("Sword", "Assets/PuzzleComp/Sword.png");
	assets->AddTexture("Hat_Blue", "Assets/PuzzleComp/Hat_Blue.png");
	assets->AddTexture("Shirt_Purple", "Assets/PuzzleComp/Shirt_Purple.png");
	assets->AddTexture("Bush", "Assets/PuzzleComp/Bush.png");

	// Place Holders for general puzzle pieces that are part of scene or characters
	assets->AddTexture("LittleJohnPH", "Assets/PuzzleComp/PlaceHolders/LittleJohnPH.png"); // 0B
	assets->AddTexture("TinkerPH", "Assets/PuzzleComp/PlaceHolders/TinkerPH.png"); // 1B
	assets->AddTexture("BeerCaskPH", "Assets/PuzzleComp/PlaceHolders/BeerCaskPH.png"); // 1B
	assets->AddTexture("FightPH", "Assets/PuzzleComp/PlaceHolders/FightPH1.png"); // 1C, 3A, 4A
	assets->AddTexture("FightPH2", "Assets/PuzzleComp/PlaceHolders/FightPH2.png"); // 4A
	assets->AddTexture("FightPH3", "Assets/PuzzleComp/PlaceHolders/FightPH3.png"); // 4A
	assets->AddTexture("FightPH4", "Assets/PuzzleComp/PlaceHolders/FightPH4.png");
	assets->AddTexture("ArrowTargetPH", "Assets/PuzzleComp/PlaceHolders/ArrowTargetPH.png"); // 1D
	assets->AddTexture("TrophyPH", "Assets/PuzzleComp/PlaceHolders/TrophyPH.png"); // 1D
	assets->AddTexture("StutleyPH", "Assets/PuzzleComp/PlaceHolders/StutleyPH.png"); // 1E
	assets->AddTexture("ScarletPH", "Assets/PuzzleComp/PlaceHolders/ScarletPH.png"); // 3A
	assets->AddTexture("TuckPH", "Assets/PuzzleComp/PlaceHolders/TuckPH.png"); // 4A

	// Place Holders for dialogue puzzle pieces/elements
	assets->AddTexture("DialoguePuzzle1", "Assets/PuzzleComp/Dialogue/DialoguePuzzle1.png"); // 1A, 2A
	assets->AddTexture("DialoguePuzzle2", "Assets/PuzzleComp/Dialogue/DialoguePuzzle2.png"); // 1A, 2A
	assets->AddTexture("DialoguePuzzle3", "Assets/PuzzleComp/Dialogue/DialoguePuzzle3.png"); // 
	assets->AddTexture("DialoguePuzzle4", "Assets/PuzzleComp/Dialogue/DialoguePuzzle4.png"); // 

	// User Interface
	assets->AddTexture("Cursor", "Assets/UI/Cursor_rough.png");


#pragma endregion TextureLibrary

	map = new TextureMap();

	// Load Map
	//TextureMap::LoadTextureMap("Assets/CanyonRun16x16.map", 16, 16);

// Create Puzzle Systems and set values using structs
#pragma region PuzzleSystemsCreation

// Prologue Puzzle System
#pragma region PrologueSystem

	// Scene A
	puzzleSysZero->puzzlePieceOne.puzzleID = "ArrowQuiver";
	puzzleSysZero->puzzlePieceOne.storyPart = 0;
	puzzleSysZero->puzzlePieceOne.storyScene = 'A';
	puzzleSysZero->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysZero->puzzlePieceOne.lastPiece = false;
	puzzleSysZero->puzzlePieceOne.spriteID = "ArrowQuiver";
	puzzleSysZero->puzzlePieceOne.transform = std::vector<int>{ 500, 600, 200, 200, 1 };
	puzzleSysZero->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysZero->puzzlePieceTwo.puzzleID = "DeerHeart";
	puzzleSysZero->puzzlePieceTwo.storyPart = 0;
	puzzleSysZero->puzzlePieceTwo.storyScene = 'A';
	puzzleSysZero->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysZero->puzzlePieceTwo.lastPiece = true;
	puzzleSysZero->puzzlePieceTwo.spriteID = "DeerHeart";
	puzzleSysZero->puzzlePieceTwo.transform = std::vector<int>{ 1250, 600, 50, 50, 1 };
	puzzleSysZero->puzzlePieceTwo.dependencies = std::vector<std::string>{ "ArrowQuiver" };

	// Scene B
	puzzleSysZeroB->puzzlePieceOne.puzzleID = "QuarterStaff";
	puzzleSysZeroB->puzzlePieceOne.storyPart = 0;
	puzzleSysZeroB->puzzlePieceOne.storyScene = 'B';
	puzzleSysZeroB->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysZeroB->puzzlePieceOne.lastPiece = false;
	puzzleSysZeroB->puzzlePieceOne.spriteID = "QuarterStaff";
	puzzleSysZeroB->puzzlePieceOne.transform = std::vector<int>{ 1400, 750, 32, 32, 4 };
	puzzleSysZeroB->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysZeroB->puzzlePieceTwo.puzzleID = "LittleJohnPH";
	puzzleSysZeroB->puzzlePieceTwo.storyPart = 0;
	puzzleSysZeroB->puzzlePieceTwo.storyScene = 'B';
	puzzleSysZeroB->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysZeroB->puzzlePieceTwo.lastPiece = false;
	puzzleSysZeroB->puzzlePieceTwo.spriteID = "LittleJohnPH";
	puzzleSysZeroB->puzzlePieceTwo.transform = std::vector<int>{ 450, 550, 32, 32, 2 };
	puzzleSysZeroB->puzzlePieceTwo.dependencies = std::vector<std::string>{ "QuarterStaff" };

	puzzleSysZeroB->puzzlePieceThree.puzzleID = "Horn";
	puzzleSysZeroB->puzzlePieceThree.storyPart = 0;
	puzzleSysZeroB->puzzlePieceThree.storyScene = 'B';
	puzzleSysZeroB->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysZeroB->puzzlePieceThree.lastPiece = true;
	puzzleSysZeroB->puzzlePieceThree.spriteID = "Horn";
	puzzleSysZeroB->puzzlePieceThree.transform = std::vector<int>{ 200, 650, 32, 32, 2 };
	puzzleSysZeroB->puzzlePieceThree.dependencies = std::vector<std::string>{ "QuarterStaff", "LittleJohnPH"};

#pragma endregion PrologueSystem

	puzzleSysZero->CreateBaseEntity(2);
	puzzleSysZero->AddEntityComponents();
	puzzleSysZeroB->CreateBaseEntity(3);

// Part 1 Puzzle System
#pragma region Part1System

	// Scene 'A'
	puzzleSysOneA->puzzlePieceOne.puzzleID = "DialoguePuzzle1";
	puzzleSysOneA->puzzlePieceOne.storyPart = 1;
	puzzleSysOneA->puzzlePieceOne.storyScene = 'A';
	puzzleSysOneA->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysOneA->puzzlePieceOne.lastPiece = false;
	puzzleSysOneA->puzzlePieceOne.spriteID = "DialoguePuzzle1";
	puzzleSysOneA->puzzlePieceOne.transform = std::vector<int>{ 500, 600, 32, 32, 2 };
	puzzleSysOneA->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysOneA->puzzlePieceTwo.puzzleID = "DialoguePuzzle2";
	puzzleSysOneA->puzzlePieceTwo.storyPart = 1;
	puzzleSysOneA->puzzlePieceTwo.storyScene = 'A';
	puzzleSysOneA->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysOneA->puzzlePieceTwo.lastPiece = true;
	puzzleSysOneA->puzzlePieceTwo.spriteID = "DialoguePuzzle2";
	puzzleSysOneA->puzzlePieceTwo.transform = std::vector<int>{ 600, 600, 32, 32, 2 };
	puzzleSysOneA->puzzlePieceTwo.dependencies = std::vector<std::string>{ "DialoguePuzzle1" };

	// Scene 'B'
	puzzleSysOneB->puzzlePieceOne.puzzleID = "Tankard";
	puzzleSysOneB->puzzlePieceOne.storyPart = 1;
	puzzleSysOneB->puzzlePieceOne.storyScene = 'B';
	puzzleSysOneB->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysOneB->puzzlePieceOne.lastPiece = false;
	puzzleSysOneB->puzzlePieceOne.spriteID = "Tankard_Empty";
	puzzleSysOneB->puzzlePieceOne.transform = std::vector<int>{ 1200, 450, 32, 32, 2 };
	puzzleSysOneB->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysOneB->puzzlePieceTwo.puzzleID = "BeerCaskPH";
	puzzleSysOneB->puzzlePieceTwo.storyPart = 1;
	puzzleSysOneB->puzzlePieceTwo.storyScene = 'B';
	puzzleSysOneB->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysOneB->puzzlePieceTwo.lastPiece = false;
	puzzleSysOneB->puzzlePieceTwo.spriteID = "BeerCaskPH";
	puzzleSysOneB->puzzlePieceTwo.transform = std::vector<int>{ 800, 150, 32, 32, 2 };
	puzzleSysOneB->puzzlePieceTwo.dependencies = std::vector<std::string>{ "Tankard" };

	puzzleSysOneB->puzzlePieceThree.puzzleID = "TinkerPH";
	puzzleSysOneB->puzzlePieceThree.storyPart = 1;
	puzzleSysOneB->puzzlePieceThree.storyScene = 'B';
	puzzleSysOneB->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysOneB->puzzlePieceThree.lastPiece = false;
	puzzleSysOneB->puzzlePieceThree.spriteID = "TinkerPH";
	puzzleSysOneB->puzzlePieceThree.transform = std::vector<int>{ 550, 700, 32, 32, 2 };
	puzzleSysOneB->puzzlePieceThree.dependencies = std::vector<std::string>{ "Tankard", "BeerCaskPH" };

	puzzleSysOneB->puzzlePieceFour.puzzleID = "CoinPurse";
	puzzleSysOneB->puzzlePieceFour.storyPart = 1;
	puzzleSysOneB->puzzlePieceFour.storyScene = 'B';
	puzzleSysOneB->puzzlePieceFour.puzzlePieceNum = 4;
	puzzleSysOneB->puzzlePieceFour.lastPiece = true;
	puzzleSysOneB->puzzlePieceFour.spriteID = "CoinPurse";
	puzzleSysOneB->puzzlePieceFour.transform = std::vector<int>{ 300, 750, 32, 32, 3 };
	puzzleSysOneB->puzzlePieceFour.dependencies = std::vector<std::string>{ "Tankard", "BeerCaskPH", "TinkerPH" };

	// Scene 'C'
	puzzleSysOneC->puzzlePieceOne.puzzleID = "QuarterStaff2";
	puzzleSysOneC->puzzlePieceOne.storyPart = 1;
	puzzleSysOneC->puzzlePieceOne.storyScene = 'C';
	puzzleSysOneC->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysOneC->puzzlePieceOne.lastPiece = false;
	puzzleSysOneC->puzzlePieceOne.spriteID = "QuarterStaff";
	puzzleSysOneC->puzzlePieceOne.transform = std::vector<int>{ 700, 450, 32, 32, 4 };
	puzzleSysOneC->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysOneC->puzzlePieceTwo.puzzleID = "FightPH";
	puzzleSysOneC->puzzlePieceTwo.storyPart = 1;
	puzzleSysOneC->puzzlePieceTwo.storyScene = 'C';
	puzzleSysOneC->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysOneC->puzzlePieceTwo.lastPiece = false;
	puzzleSysOneC->puzzlePieceTwo.spriteID = "FightPH";
	puzzleSysOneC->puzzlePieceTwo.transform = std::vector<int>{ 550, 750, 32, 32, 2 };
	puzzleSysOneC->puzzlePieceTwo.dependencies = std::vector<std::string>{ "QuarterStaff2" };

	puzzleSysOneC->puzzlePieceThree.puzzleID = "BrokenQS";
	puzzleSysOneC->puzzlePieceThree.storyPart = 1;
	puzzleSysOneC->puzzlePieceThree.storyScene = 'C';
	puzzleSysOneC->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysOneC->puzzlePieceThree.lastPiece = false;
	puzzleSysOneC->puzzlePieceThree.spriteID = "BrokenQS";
	puzzleSysOneC->puzzlePieceThree.transform = std::vector<int>{ 750, 750, 32, 32, 4 };
	puzzleSysOneC->puzzlePieceThree.dependencies = std::vector<std::string>{ "QuarterStaff2", "FightPH" };

	puzzleSysOneC->puzzlePieceFour.puzzleID = "Horn2";
	puzzleSysOneC->puzzlePieceFour.storyPart = 1;
	puzzleSysOneC->puzzlePieceFour.storyScene = 'C';
	puzzleSysOneC->puzzlePieceFour.puzzlePieceNum = 4;
	puzzleSysOneC->puzzlePieceFour.lastPiece = true;
	puzzleSysOneC->puzzlePieceFour.spriteID = "Horn";
	puzzleSysOneC->puzzlePieceFour.transform = std::vector<int>{ 1200, 750, 32, 32, 2 };
	puzzleSysOneC->puzzlePieceFour.dependencies = std::vector<std::string>{ "QuarterStaff2", "FightPH", "BrokenQS"};

	// Scene D
	puzzleSysOneD->puzzlePieceOne.puzzleID = "Arrow";
	puzzleSysOneD->puzzlePieceOne.storyPart = 1;
	puzzleSysOneD->puzzlePieceOne.storyScene = 'D';
	puzzleSysOneD->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysOneD->puzzlePieceOne.lastPiece = false;
	puzzleSysOneD->puzzlePieceOne.spriteID = "Arrow_FlipH";
	puzzleSysOneD->puzzlePieceOne.transform = std::vector<int>{ 400, 700, 64, 32, 2 };
	puzzleSysOneD->puzzlePieceOne.dependencies = std::vector<std::string>{};
	
	puzzleSysOneD->puzzlePieceTwo.puzzleID = "ArrowTargetPH";
	puzzleSysOneD->puzzlePieceTwo.storyPart = 1;
	puzzleSysOneD->puzzlePieceTwo.storyScene = 'D';
	puzzleSysOneD->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysOneD->puzzlePieceTwo.lastPiece = false;
	puzzleSysOneD->puzzlePieceTwo.spriteID = "ArrowTargetPH";
	puzzleSysOneD->puzzlePieceTwo.transform = std::vector<int>{ 200, 500, 32, 32, 2 };
	puzzleSysOneD->puzzlePieceTwo.dependencies = std::vector<std::string>{ "Arrow" };

	puzzleSysOneD->puzzlePieceThree.puzzleID = "TrophyPH";
	puzzleSysOneD->puzzlePieceThree.storyPart = 1;
	puzzleSysOneD->puzzlePieceThree.storyScene = 'D';
	puzzleSysOneD->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysOneD->puzzlePieceThree.lastPiece = true;
	puzzleSysOneD->puzzlePieceThree.spriteID = "TrophyPH";
	puzzleSysOneD->puzzlePieceThree.transform = std::vector<int>{ 600, 600, 32, 32, 2 };
	puzzleSysOneD->puzzlePieceThree.dependencies = std::vector<std::string>{ "Arrow", "ArrowTargetPH" };

	// Scene E
	puzzleSysOneE->puzzlePieceOne.puzzleID = "Cloak_Blue";
	puzzleSysOneE->puzzlePieceOne.storyPart = 1;
	puzzleSysOneE->puzzlePieceOne.storyScene = 'E';
	puzzleSysOneE->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysOneE->puzzlePieceOne.lastPiece = false;
	puzzleSysOneE->puzzlePieceOne.spriteID = "Cloak_Blue";
	puzzleSysOneE->puzzlePieceOne.transform = std::vector<int>{ 450, 650, 64, 128, 1 };
	puzzleSysOneE->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysOneE->puzzlePieceTwo.puzzleID = "Cloak_Brown";
	puzzleSysOneE->puzzlePieceTwo.storyPart = 1;
	puzzleSysOneE->puzzlePieceTwo.storyScene = 'E';
	puzzleSysOneE->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysOneE->puzzlePieceTwo.lastPiece = false;
	puzzleSysOneE->puzzlePieceTwo.spriteID = "Cloak_Brown";
	puzzleSysOneE->puzzlePieceTwo.transform = std::vector<int>{ 650, 650, 64, 128, 1 };
	puzzleSysOneE->puzzlePieceTwo.dependencies = {};

	puzzleSysOneE->puzzlePieceThree.puzzleID = "QuarterStaff3";
	puzzleSysOneE->puzzlePieceThree.storyPart = 1;
	puzzleSysOneE->puzzlePieceThree.storyScene = 'E';
	puzzleSysOneE->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysOneE->puzzlePieceThree.lastPiece = false;
	puzzleSysOneE->puzzlePieceThree.spriteID = "QuarterStaff";
	puzzleSysOneE->puzzlePieceThree.transform = std::vector<int>{ 300, 650, 32, 32, 4 };
	puzzleSysOneE->puzzlePieceThree.dependencies = std::vector<std::string>{ "Cloak_Blue", "Cloak_Brown" };

	puzzleSysOneE->puzzlePieceFour.puzzleID = "StutleyPH";
	puzzleSysOneE->puzzlePieceFour.storyPart = 1;
	puzzleSysOneE->puzzlePieceFour.storyScene = 'E';
	puzzleSysOneE->puzzlePieceFour.puzzlePieceNum = 4;
	puzzleSysOneE->puzzlePieceFour.lastPiece = true;
	puzzleSysOneE->puzzlePieceFour.spriteID = "StutleyPH";
	puzzleSysOneE->puzzlePieceFour.transform = std::vector<int>{ 750, 500, 32, 32, 2 };
	puzzleSysOneE->puzzlePieceFour.dependencies = std::vector<std::string>{ "Cloak_Blue", "Cloak_Brown", "QuarterStaff3" };

#pragma endregion Part1System

	puzzleSysOneA->CreateBaseEntity(2);
	puzzleSysOneB->CreateBaseEntity(4);
	puzzleSysOneC->CreateBaseEntity(4);
	puzzleSysOneD->CreateBaseEntity(4);
	puzzleSysOneE->CreateBaseEntity(4);

#pragma region Part2System
	
	// Scene A
	puzzleSysTwoA->puzzlePieceOne.puzzleID = "DialoguePuzzle1.2A";
	puzzleSysTwoA->puzzlePieceOne.storyPart = 2;
	puzzleSysTwoA->puzzlePieceOne.storyScene = 'A';
	puzzleSysTwoA->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysTwoA->puzzlePieceOne.lastPiece = false;
	puzzleSysTwoA->puzzlePieceOne.spriteID = "DialoguePuzzle1";
	puzzleSysTwoA->puzzlePieceOne.transform = std::vector<int>{ 400, 700, 32, 32, 2 };
	puzzleSysTwoA->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysTwoA->puzzlePieceTwo.puzzleID = "DialoguePuzzle2.2A";
	puzzleSysTwoA->puzzlePieceTwo.storyPart = 2;
	puzzleSysTwoA->puzzlePieceTwo.storyScene = 'A';
	puzzleSysTwoA->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysTwoA->puzzlePieceTwo.lastPiece = true;
	puzzleSysTwoA->puzzlePieceTwo.spriteID = "DialoguePuzzle2";
	puzzleSysTwoA->puzzlePieceTwo.transform = std::vector<int>{ 500, 700, 32, 32, 2 };
	puzzleSysTwoA->puzzlePieceTwo.dependencies = std::vector<std::string>{ "DialoguePuzzle1.2A" };

	// Scene B
	puzzleSysTwoB->puzzlePieceOne.puzzleID = "PorkRibs.2B";
	puzzleSysTwoB->puzzlePieceOne.storyPart = 2;
	puzzleSysTwoB->puzzlePieceOne.storyScene = 'B';
	puzzleSysTwoB->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysTwoB->puzzlePieceOne.lastPiece = false;
	puzzleSysTwoB->puzzlePieceOne.spriteID = "PorkRibs";
	puzzleSysTwoB->puzzlePieceOne.transform = std::vector<int>{ 200, 200, 32, 32, 2 };
	puzzleSysTwoB->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysTwoB->puzzlePieceTwo.puzzleID = "TurkeyLeg.2B";
	puzzleSysTwoB->puzzlePieceTwo.storyPart = 2;
	puzzleSysTwoB->puzzlePieceTwo.storyScene = 'B';
	puzzleSysTwoB->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysTwoB->puzzlePieceTwo.lastPiece = false;
	puzzleSysTwoB->puzzlePieceTwo.spriteID = "TurkeyLeg";
	puzzleSysTwoB->puzzlePieceTwo.transform = std::vector<int>{ 400, 200, 32, 32, 2 };
	puzzleSysTwoB->puzzlePieceTwo.dependencies = std::vector<std::string>{ "PorkRibs.2B" };

	puzzleSysTwoB->puzzlePieceThree.puzzleID = "Steak.2B";
	puzzleSysTwoB->puzzlePieceThree.storyPart = 2;
	puzzleSysTwoB->puzzlePieceThree.storyScene = 'B';
	puzzleSysTwoB->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysTwoB->puzzlePieceThree.lastPiece = false;
	puzzleSysTwoB->puzzlePieceThree.spriteID = "Steak";
	puzzleSysTwoB->puzzlePieceThree.transform = std::vector<int>{ 600, 200, 32, 32, 2 };
	puzzleSysTwoB->puzzlePieceThree.dependencies = std::vector<std::string>{ "PorkRibs.2B", "TurkeyLeg.2B" };

	puzzleSysTwoB->puzzlePieceFour.puzzleID = "CoinStack.2B";
	puzzleSysTwoB->puzzlePieceFour.storyPart = 2;
	puzzleSysTwoB->puzzlePieceFour.storyScene = 'B';
	puzzleSysTwoB->puzzlePieceFour.puzzlePieceNum = 4;
	puzzleSysTwoB->puzzlePieceFour.lastPiece = true;
	puzzleSysTwoB->puzzlePieceFour.spriteID = "Coin_Stack";
	puzzleSysTwoB->puzzlePieceFour.transform = std::vector<int>{ 800, 200, 32, 32, 2 };
	puzzleSysTwoB->puzzlePieceFour.dependencies = std::vector<std::string>{ "PorkRibs.2B", "TurkeyLeg.2B", "Steak.2B"};

	// Scene C
	puzzleSysTwoC->puzzlePieceOne.puzzleID = "Wine.2C";
	puzzleSysTwoC->puzzlePieceOne.storyPart = 2;
	puzzleSysTwoC->puzzlePieceOne.storyScene = 'C';
	puzzleSysTwoC->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysTwoC->puzzlePieceOne.lastPiece = false;
	puzzleSysTwoC->puzzlePieceOne.spriteID = "Wine";
	puzzleSysTwoC->puzzlePieceOne.transform = std::vector<int>{ 400, 600, 32, 32, 2 };
	puzzleSysTwoC->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysTwoC->puzzlePieceTwo.puzzleID = "TurkeyLeg.2C";
	puzzleSysTwoC->puzzlePieceTwo.storyPart = 2;
	puzzleSysTwoC->puzzlePieceTwo.storyScene = 'C';
	puzzleSysTwoC->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysTwoC->puzzlePieceTwo.lastPiece = false;
	puzzleSysTwoC->puzzlePieceTwo.spriteID = "TurkeyLeg";
	puzzleSysTwoC->puzzlePieceTwo.transform = std::vector<int>{ 200, 600, 32, 32, 2 };
	puzzleSysTwoC->puzzlePieceTwo.dependencies = std::vector<std::string>{ "Wine.2C" };

	puzzleSysTwoC->puzzlePieceThree.puzzleID = "CoinPurse.2C";
	puzzleSysTwoC->puzzlePieceThree.storyPart = 2;
	puzzleSysTwoC->puzzlePieceThree.storyScene = 'C';
	puzzleSysTwoC->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysTwoC->puzzlePieceThree.lastPiece = true;
	puzzleSysTwoC->puzzlePieceThree.spriteID = "CoinPurse";
	puzzleSysTwoC->puzzlePieceThree.transform = std::vector<int>{ 600, 600, 32, 32, 2 };
	puzzleSysTwoC->puzzlePieceThree.dependencies = std::vector<std::string>{ "Wine.2C", "TurkeyLeg.2C"};

#pragma endregion Part2System

	puzzleSysTwoA->CreateBaseEntity(2);
	puzzleSysTwoB->CreateBaseEntity(4);
	puzzleSysTwoC->CreateBaseEntity(3);

#pragma region Part3System

	// Scene A
	puzzleSysThreeA->puzzlePieceOne.puzzleID = "QuarterStaff.3A";
	puzzleSysThreeA->puzzlePieceOne.storyPart = 3;
	puzzleSysThreeA->puzzlePieceOne.storyScene = 'A';
	puzzleSysThreeA->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysThreeA->puzzlePieceOne.lastPiece = false;
	puzzleSysThreeA->puzzlePieceOne.spriteID = "QuarterStaff";
	puzzleSysThreeA->puzzlePieceOne.transform = std::vector<int>{ 600, 600, 32, 32, 4 };
	puzzleSysThreeA->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysThreeA->puzzlePieceTwo.puzzleID = "ScarletPH.3A";
	puzzleSysThreeA->puzzlePieceTwo.storyPart = 3;
	puzzleSysThreeA->puzzlePieceTwo.storyScene = 'A';
	puzzleSysThreeA->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysThreeA->puzzlePieceTwo.lastPiece = false;
	puzzleSysThreeA->puzzlePieceTwo.spriteID = "ScarletPH";
	puzzleSysThreeA->puzzlePieceTwo.transform = std::vector<int>{ 400, 400, 32, 32, 4 };
	puzzleSysThreeA->puzzlePieceTwo.dependencies = std::vector<std::string>{ "QuarterStaff.3A" };

	puzzleSysThreeA->puzzlePieceThree.puzzleID = "FightPH.3A";
	puzzleSysThreeA->puzzlePieceThree.storyPart = 3;
	puzzleSysThreeA->puzzlePieceThree.storyScene = 'A';
	puzzleSysThreeA->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysThreeA->puzzlePieceThree.lastPiece = true;
	puzzleSysThreeA->puzzlePieceThree.spriteID = "FightPH";
	puzzleSysThreeA->puzzlePieceThree.transform = std::vector<int>{ 800, 400, 32, 32, 4 };
	puzzleSysThreeA->puzzlePieceThree.dependencies = std::vector<std::string>{ "QuarterStaff.3A", "ScarletPH.3A" };

#pragma endregion Part3System

	puzzleSysThreeA->CreateBaseEntity(3);

#pragma region Part4System

	// Scene A
	puzzleSysFourA->puzzlePieceOne.puzzleID = "FightPH1.4A";
	puzzleSysFourA->puzzlePieceOne.storyPart = 4;
	puzzleSysFourA->puzzlePieceOne.storyScene = 'A';
	puzzleSysFourA->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysFourA->puzzlePieceOne.lastPiece = false;
	puzzleSysFourA->puzzlePieceOne.spriteID = "FightPH";
	puzzleSysFourA->puzzlePieceOne.transform = std::vector<int>{ 200, 200, 32, 32, 2 };
	puzzleSysFourA->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysFourA->puzzlePieceTwo.puzzleID = "FightPH2.4A";
	puzzleSysFourA->puzzlePieceTwo.storyPart = 4;
	puzzleSysFourA->puzzlePieceTwo.storyScene = 'A';
	puzzleSysFourA->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysFourA->puzzlePieceTwo.lastPiece = false;
	puzzleSysFourA->puzzlePieceTwo.spriteID = "FightPH2";
	puzzleSysFourA->puzzlePieceTwo.transform = std::vector<int>{ 400, 200, 32, 32, 2 };
	puzzleSysFourA->puzzlePieceTwo.dependencies = std::vector<std::string>{ "FightPH1.4A" };

	puzzleSysFourA->puzzlePieceThree.puzzleID = "FightPH3.4A";
	puzzleSysFourA->puzzlePieceThree.storyPart = 4;
	puzzleSysFourA->puzzlePieceThree.storyScene = 'A';
	puzzleSysFourA->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysFourA->puzzlePieceThree.lastPiece = false;
	puzzleSysFourA->puzzlePieceThree.spriteID = "FightPH3";
	puzzleSysFourA->puzzlePieceThree.transform = std::vector<int>{ 600, 200, 32, 32, 2 };
	puzzleSysFourA->puzzlePieceThree.dependencies = std::vector<std::string>{ "FightPH1.4A", "FightPH2.4A"};

	puzzleSysFourA->puzzlePieceFour.puzzleID = "FightPH4.4A";
	puzzleSysFourA->puzzlePieceFour.storyPart = 4;
	puzzleSysFourA->puzzlePieceFour.storyScene = 'A';
	puzzleSysFourA->puzzlePieceFour.puzzlePieceNum = 4;
	puzzleSysFourA->puzzlePieceFour.lastPiece = true;
	puzzleSysFourA->puzzlePieceFour.spriteID = "FightPH4";
	puzzleSysFourA->puzzlePieceFour.transform = std::vector<int>{ 800, 200, 32, 32, 2 };
	puzzleSysFourA->puzzlePieceFour.dependencies = std::vector<std::string>{ "FightPH1.4A", "FightPH2.4A", "FightPH3.4A"};

	// Scene B
	puzzleSysFourB->puzzlePieceOne.puzzleID = "Shirt_BlueGray.4B";
	puzzleSysFourB->puzzlePieceOne.storyPart = 4;
	puzzleSysFourB->puzzlePieceOne.storyScene = 'B';
	puzzleSysFourB->puzzlePieceOne.puzzlePieceNum = 1;
	puzzleSysFourB->puzzlePieceOne.lastPiece = false;
	puzzleSysFourB->puzzlePieceOne.spriteID = "Shirt_BlueGray";
	puzzleSysFourB->puzzlePieceOne.transform = std::vector<int>{ 200, 200, 32, 32, 2 };
	puzzleSysFourB->puzzlePieceOne.dependencies = std::vector<std::string>{};

	puzzleSysFourB->puzzlePieceTwo.puzzleID = "Hat_Red.4B";
	puzzleSysFourB->puzzlePieceTwo.storyPart = 4;
	puzzleSysFourB->puzzlePieceTwo.storyScene = 'B';
	puzzleSysFourB->puzzlePieceTwo.puzzlePieceNum = 2;
	puzzleSysFourB->puzzlePieceTwo.lastPiece = false;
	puzzleSysFourB->puzzlePieceTwo.spriteID = "Hat_Red";
	puzzleSysFourB->puzzlePieceTwo.transform = std::vector<int>{ 400, 200, 32, 32, 2 };
	puzzleSysFourB->puzzlePieceTwo.dependencies = std::vector<std::string>{ "Shirt_BlueGray.4B" };

	puzzleSysFourB->puzzlePieceThree.puzzleID = "Harp.4B";
	puzzleSysFourB->puzzlePieceThree.storyPart = 4;
	puzzleSysFourB->puzzlePieceThree.storyScene = 'B';
	puzzleSysFourB->puzzlePieceThree.puzzlePieceNum = 3;
	puzzleSysFourB->puzzlePieceThree.lastPiece = true;
	puzzleSysFourB->puzzlePieceThree.spriteID = "Harp";
	puzzleSysFourB->puzzlePieceThree.transform = std::vector<int>{ 600, 200, 32, 32, 2 };
	puzzleSysFourB->puzzlePieceThree.dependencies = std::vector<std::string>{ puzzleSysFourB->puzzlePieceOne.puzzleID, puzzleSysFourB->puzzlePieceTwo.puzzleID };

#pragma endregion Part4System
	
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

	littleJohn.addComponent<TransformComponent>(300.0f, 300.0f, 400, 400, 1);
	littleJohn.addComponent<SpriteComponent>("LittleJohnQS", false);
	littleJohn.AddGroup(groupCharacterSprites);

	sheriff.addComponent<TransformComponent>(300.0f, 300.0f, 400, 400, 1);
	sheriff.addComponent<SpriteComponent>("TheSheriff", false);
	sheriff.AddGroup(groupCharacterSprites);

	npcOne.addComponent<TransformComponent>(200.0f, 400.0f, 400, 400, 1);
	npcOne.addComponent<SpriteComponent>("RangerSprite", true);
	npcOne.AddGroup(groupCharacterSprites);

	npcTwo.addComponent<TransformComponent>(200.0f, 400.0f, 400, 400, 1);
	npcTwo.addComponent<SpriteComponent>("PeasantTwo", false);
	npcTwo.AddGroup(groupCharacterSprites);

	npcThree.addComponent<TransformComponent>(200.0f, 400.0f, 400, 400, 1);
	npcThree.addComponent<SpriteComponent>("PeasantThree", false);
	npcThree.AddGroup(groupCharacterSprites);

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

void Game::DisplayText()
{
	std::string tempString = "";
	int placeHolder = 100;

	while (placeHolder < 1600)
	{
		tempString = std::to_string(placeHolder);
		gameMode->TextSetter(renderer, "Assets/arial.ttf", 16, tempString, { 255, 0, 0, 255 });
		gameMode->DisplayOnScreenText(placeHolder, 20, renderer);

		placeHolder = placeHolder + 100;
	}

	placeHolder = 100;

	while (placeHolder < 1000)
	{
		tempString = std::to_string(placeHolder);
		gameMode->TextSetter(renderer, "Assets/arial.ttf", 16, tempString, { 255, 0, 0, 255 });
		gameMode->DisplayOnScreenText(40, placeHolder, renderer);

		placeHolder = placeHolder + 100;
	}
}

void Game::DebugOne()
{
	std::cout << "DebugOne()" << std::endl;
	
	std::cout << "puzzleSysTwoB map size: " << assets->GetMapSize() << std::endl;

	std::cout << "puzzleSysTwoB map element ids" << std::endl;
	assets->GetMapElements();

	std::cout << "Manual ID PRINT" << std::endl;
	std::cout << "------------------------------" << std::endl;
	std::cout << "puzzleSysTwoB->puzzlePieceOne.puzzleID: " << puzzleSysTwoB->puzzlePieceOne.puzzleID << std::endl;
	std::cout << "puzzleSysTwoB->puzzlePieceTwo.puzzleID: " << puzzleSysTwoB->puzzlePieceTwo.puzzleID << std::endl;
	std::cout << "puzzleSysTwoB->puzzlePieceThree.puzzleID: " << puzzleSysTwoB->puzzlePieceThree.puzzleID << std::endl;
	std::cout << "puzzleSysTwoB->puzzlePieceFour.puzzleID: " << puzzleSysTwoB->puzzlePieceFour.puzzleID << std::endl;
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

int GameMode::storyPart = 0;
char GameMode::storyScene = 'A';

GameMode::GameMode()
{
	clickedPuzzlePiece = nullptr;
}

GameMode::~GameMode()
{

}

#pragma region DisplayText

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

void GameMode::DisplayOnScreenText(int xPos, int yPos, SDL_Renderer* _renderer)
{
	textRect.x = xPos;
	textRect.y = yPos;
	SDL_RenderCopy(_renderer, textTexture, nullptr, &textRect);
}

#pragma endregion DisplayText

// Getters and Setters
#pragma region GetSet
void GameMode::SetStoryPart(int part)
{
	storyPart = part;
}

int GameMode::GetStoryPart()
{
	return storyPart;
}

void GameMode::SetStoryScene(char scene)
{
	GameMode::storyScene = scene;
}

char GameMode::GetStoryScene()
{
	return storyScene;
}
#pragma endregion GetSet

// Function is called from PuzzlePieceComponent
// When the last piece of a puzzle is used
void GameMode::ManageStoryPart(int part, char scene)
{

	std::cout << "GameMode::ManageStoryPart()" << std::endl;

	std::cout << "scene: " << scene << std::endl;
	std::cout << "storyScene: " << storyScene << std::endl;

	// Error handling
	if (part != storyPart)
	{
		std::cout << "\n\n\n\n" << "----------------" << std::endl;
		std::cout << "ERROR:Story parts don't align" << std::endl;
		std::cout << "----------------" << "\n\n\n\n" << std::endl;
	}

	if (storyScene != scene)
	{
		std::cout << "\n\n\n\n" << "----------------" << std::endl;
		std::cout << "ERROR:Story scenes don't align" << std::endl;
		std::cout << "----------------" << "\n\n\n\n" << std::endl;
	}

	// switch case to determine which story part is next
	switch (part)
	{
	case 0: // Prologue

		if (storyScene == 'A')
		{
			PrologueSceneB();
		}
		else
		{
			Part1SceneA();
		}
		break;

	case 1:

		if (storyScene == 'A')
		{
			Part1SceneB();
			break;
		}
		else if (storyScene == 'B')
		{
			Part1SceneC();
			break;
		}
		else if (storyScene == 'C')
		{
			Part1SceneD();
			break;
		}
		else if (storyScene == 'D')
		{
			std::cout << "ManageStoryPart() Part: 1, Scene: D" << std::endl;
			Part1SceneE();
			break;
		}
		else if (storyScene == 'E')
		{
			std::cout << "ManageStoryPart() Part: 1, Scene: E" << std::endl;
			Part2SceneA();
			break;
		}
		break;

	case 2:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 2, Scene: A" << std::endl;
			Part2SceneB();
			break;
		}
		else if (storyScene == 'B')
		{
			std::cout << "ManageStoryPart() Part: 2, Scene: B" << std::endl;
			Part2SceneC();
			break;
		}
		else if (storyScene == 'C')
		{
			std::cout << "ManageStoryPart() Part: 2, Scene: C" << std::endl;
			Part3SceneA();
			break;
		}
		break;

	case 3:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 3, Scene: A" << std::endl;
			Part4SceneA();
			break;
		}
		break;

	case 4:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 4, Scene: A" << std::endl;
			Part4SceneB();
			break;
		}
		else if (storyScene == 'B')
		{
			std::cout << "ManageStoryPart() Part: 4, Scene: B" << std::endl;
			Part5SceneA();
			break;
		}
		break;

	case 5:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 5, Scene: A" << std::endl;
			Part6SceneA();
			break;
		}
		break;

	case 6:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 6, Scene: A" << std::endl;
			Part6SceneB();
			break;
		}
		else if (storyScene == 'B')
		{
			std::cout << "ManageStoryPart() Part: 6, Scene: B" << std::endl;
			Part7SceneA();
			break;
		}
		break;

	case 7:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 7, Scene: A" << std::endl;
			Part7SceneB();
			break;
		}
		else if (storyScene == 'B')
		{
			std::cout << "ManageStoryPart() Part: 7, Scene: B" << std::endl;
			Part8SceneA();
			break;
		}
		break;

	case 8:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 8, Scene: A" << std::endl;
			Part8SceneB();
			break;
		}
		else if (storyScene == 'B')
		{
			std::cout << "ManageStoryPart() Part: 8, Scene: B" << std::endl;
			Part9SceneA();
			break;
		}
		break;

	case 9:
		if (storyScene == 'A')
		{
			std::cout << "ManageStoryPart() Part: 9, Scene: A" << std::endl;
			break;
		}
		else
		{
			GameComplete();
		}
		break;

	default:
		break;
	}

}

void GameMode::UpdateBackgroundScene(std::string sceneID)
{
	backgroundScene.getComponent<SpriteComponent>().SetNewTexture(sceneID);
}

bool GameMode::PuzzleCollisionCheck()
{
	SDL_Rect playerCollider = player.getComponent<CollisionComponent>().collider;

	for (auto& p : puzzlePieces)
	{
		//std::cout << "PuzzlePiece id: " << p->getComponent<PuzzlePieceComponent>().pieceName
			//<< std::endl;

		SDL_Rect tempCol;

		if (p->hasComponent<SpriteComponent>())
		{
			tempCol = p->getComponent<CollisionComponent>().collider;
		}		

		if (Collision::AABB(playerCollider, tempCol))
		{

			//std::cout << "Player x PuzzlePiece collision" << std::endl;
			clickedPuzzlePiece = p;

			return true;
		}
		else
		{
			//std::cout << "No Player x PuzzlePiece collision" << std::endl;
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

#pragma region PrologueLoads
void GameMode::PrologueSceneB()
{
	std::cout << "\nPrologueSceneB() GameMode Loader" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin meets Little John and engages him in a fight" <<
		" with quarter staffs. Upon losing, Robin uses his horn to call the rest of his " <<
		"merry men. They convince Little John to join them.\n" << std::endl;

	// Set previous puzzle to solved
	puzzleSysZero->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryScene('B');

	// Add components to entities
	puzzleSysZeroB->AddEntityComponents();

	// Update background scene
	backgroundScene.getComponent<SpriteComponent>().SetNewTexture("RobinFightsLJ");

	// Character management, if required
	robinHood.getComponent<SpriteComponent>().SetNewTexture("RobinSpriteQS");
	littleJohn.getComponent<SpriteComponent>().SetToggleDraw(true);
	npcOne.getComponent<SpriteComponent>().SetToggleDraw(false);

	// Delete old entities and maps, manage puzzles
	puzzleSysZero->DestroyPuzzlePieces(0, 'A');
	assets->ClearPuzzlePieceMap(0, 'A');

	// Update puzzle piece assets, old code
	/*
	assets->GetPuzzlePiece(puzzleSysZero->puzzlePieceOne.puzzleID)->getComponent<SpriteComponent>().SetToggleDraw(false);
	assets->GetPuzzlePiece(puzzleSysZero->puzzlePieceTwo.puzzleID)->getComponent<SpriteComponent>().SetToggleDraw(false);
	assets->GetPuzzlePiece(puzzleSysZeroB->puzzlePieceOne.puzzleID)->getComponent<SpriteComponent>().SetToggleDraw(true);
	assets->GetPuzzlePiece(puzzleSysZeroB->puzzlePieceTwo.puzzleID)->getComponent<SpriteComponent>().SetToggleDraw(true);
	assets->GetPuzzlePiece(puzzleSysZeroB->puzzlePieceThree.puzzleID)->getComponent<SpriteComponent>().SetToggleDraw(true);
	*/
}
#pragma endregion PrologueLoads

#pragma region Part1Loads
void GameMode::Part1SceneA()
{
	std::cout << "\nPart1SceneA() GameMode Loader" << std::endl;

	// Output basic story point
	std::cout << "Story Point: Robin meets 'The Tinker' in Sherwood Forest. He is able to " <<
		"convince him that he is not Robin Hood but he knows that Robin frequents the Blue Boar." <<
		"The pair set off towards the Blue Boar.\n" << std::endl;

	// Update puzzle status to solved for previous Story Part Puzzle Systems
	puzzleSysZeroB->SetPuzzleStatus(true);

	// Update story part and scene
	SetStoryPart(1);
	SetStoryScene('A');

	// Add components to entities
	puzzleSysOneA->AddEntityComponents();

	// Change background
	backgroundScene.getComponent<SpriteComponent>().SetNewTexture("SherwoodForest1");

	// Place characters
	robinHood.getComponent<SpriteComponent>().SetNewTexture("RobinSprite");
	robinHood.getComponent<TransformComponent>().SetNewTransformPos(650.0f, 550.0f);
	littleJohn.getComponent<SpriteComponent>().SetToggleDraw(false);
	npcOne.getComponent<TransformComponent>().SetNewTransformPos(250.0f, 550.0f);
	npcOne.getComponent<SpriteComponent>().SetNewTexture("TheTinker");
	npcOne.getComponent<SpriteComponent>().SetToggleDraw(true);

	// Manage puzzle
	puzzleSysZeroB->DestroyPuzzlePieces(0, 'B');
	assets->ClearPuzzlePieceMap(0, 'B');
}

void GameMode::Part1SceneB()
{
	std::cout << "\nPart1SceneB() GameMode Loader" << std::endl;

	// Output Story Point
	std::cout << "StoryStory Point: Getting The Tinker drunk and stealing his stuff." << std::endl;

	// Set previous puzzle to solved
	puzzleSysOneA->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(1);
	SetStoryScene('B');

	// Add components to entities
	puzzleSysOneB->AddEntityComponents();

	// Update background scene
	backgroundScene.getComponent<SpriteComponent>().SetNewTexture("BlueBoarInt");

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
	puzzleSysOneA->DestroyPuzzlePieces(1, 'A');
	assets->ClearPuzzlePieceMap(1, 'A');

}

void GameMode::Part1SceneC()
{
	std::cout << "\nPart1SceneC() GameMode Loader" << std::endl;

	// Output basic story point
	std::cout << "Story Point: The Tinker woke up after Robin stole his things. He forces the owner" <<
		" of the Blue Boar to tell him who stole his stuff and where they went. After making The Tinker" <<
		" pay his bill with his weapons, the barmen tells The Tinker that Robin Hood is who he was " <<
		"drinking with but not that Robin stole his things. The Tinker chases after Robin in Sherwood " <<
		"When he catches Robin they fight, The Tinker breaks Robins staff, and then Robin uses his horn " <<
		"to call his merry men. When they arrive they convince The Tinker to join them.\n" << std::endl;

	// Update story part and scene
	SetStoryPart(1);
	SetStoryScene('C');

	// Add components to entities
	puzzleSysOneC->AddEntityComponents();

	// Update background scene
	backgroundScene.getComponent<SpriteComponent>().SetNewTexture("SherwoodForest2");

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
	puzzleSysOneB->DestroyPuzzlePieces(1, 'B');
	assets->ClearPuzzlePieceMap(1, 'B');
}

void GameMode::Part1SceneD()
{
	// Output statement for loader execution
	std::cout << "\nPart1SceneD()" << std::endl;

	// Output Story Point
	std::cout << "Story Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved
	puzzleSysOneC->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(1);
	SetStoryScene('D');

	// Add components to entities
	puzzleSysOneD->AddEntityComponents();

	// Update background scene
	backgroundScene.getComponent<SpriteComponent>().SetNewTexture("ArcheryComp");

	// Character management, if required
	npcOne.getComponent<SpriteComponent>().SetToggleDraw(false);
	sheriff.getComponent<SpriteComponent>().SetToggleDraw(true);
	sheriff.getComponent<TransformComponent>().SetNewTransformPos(100.0f, 550.0f);
	littleJohn.getComponent<SpriteComponent>().SetToggleDraw(true);
	littleJohn.getComponent<TransformComponent>().SetNewTransformPos(850.0f, 550.0f);
	robinHood.getComponent<TransformComponent>().SetNewTransformPos(500.0f, 550.0f);
	robinHood.getComponent<SpriteComponent>().HorizontalFlip();
	

	// Delete old entities and maps, Manage Puzzle
	puzzleSysOneC->DestroyPuzzlePieces(1, 'C');
	assets->ClearPuzzlePieceMap(1, 'C');
}

void GameMode::Part1SceneE()
{
	// Output statement for loader execution
	std::cout << "\nPart1SceneE()" << std::endl;

	// Output Story Point
	std::cout << "Story Point: The rescue of Stutley from the noose and The Sheriff in Nottingham Square" << std::endl;

	// Set previous puzzle to solved
	puzzleSysOneD->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(1);
	SetStoryScene('E');

	// Add components to entities
	puzzleSysOneE->AddEntityComponents();

	// Update background scene
	backgroundScene.getComponent<SpriteComponent>().SetNewTexture("HangmansNoose");

	// Character management, if required
	npcOne.getComponent<SpriteComponent>().SetToggleDraw(true);
	npcOne.getComponent<SpriteComponent>().SetNewTexture("Stutley");
	npcOne.getComponent<TransformComponent>().SetNewTransformPos(600.0f, 300.0f);
	sheriff.getComponent<TransformComponent>().SetNewTransformPos(1000.0f, 300.0f);
	littleJohn.getComponent<TransformComponent>().SetNewTransformPos(50.0f, 500.0f);
	robinHood.getComponent<TransformComponent>().SetNewTransformPos(1200.0f, 500.0f);

	// Delete old entities and maps, Manage Puzzle
	puzzleSysOneD->DestroyPuzzlePieces(1, 'D');
	assets->ClearPuzzlePieceMap(1, 'D');
}

#pragma endregion Part1Loads

#pragma region Part2Loads

void GameMode::Part2SceneA()
{
	std::cout << "\nPart2SceneA()" << std::endl;

	// Output Story Point
	std::cout << "Story Point: Robin pays the butcher to swap places with him and allow Robin to sell the wares in Nottingham Square" << std::endl;

	// Set previous puzzle to solved
	puzzleSysOneE->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(2);
	SetStoryScene('A');

	// Add components to entities
	puzzleSysTwoA->AddEntityComponents();

	// Update background scene
	UpdateBackgroundScene("SherwoodForestRoad");

	// Character management, if required
	npcOne.getComponent<SpriteComponent>().SetNewTexture("Butcher");
	npcOne.getComponent<TransformComponent>().SetNewTransformPos(250.0f, 550.0f);
	littleJohn.getComponent<SpriteComponent>().SetToggleDraw(false);
	sheriff.getComponent<SpriteComponent>().SetToggleDraw(false);

	// Delete old entities and maps, Manage Puzzle
	puzzleSysOneE->DestroyPuzzlePieces(1, 'E');
	assets->ClearPuzzlePieceMap(1, 'E');
	puzzleSysZero->~PuzzleSystem();
	puzzleSysZeroB->~PuzzleSystem();
	puzzleSysOneA->~PuzzleSystem();
	puzzleSysOneB->~PuzzleSystem();
	puzzleSysOneC->~PuzzleSystem();
	puzzleSysOneD->~PuzzleSystem();
	puzzleSysOneE->~PuzzleSystem();
}

void GameMode::Part2SceneB()
{
	std::cout << "\nPart2SceneB()" << std::endl;

	// Output Story Point
	std::cout << "Story Point: Robin outsells all the other butchers at Nottingham Square" << std::endl;

	// Set previous puzzle to solved
	puzzleSysTwoA->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(2);
	SetStoryScene('B');

	// Add components to entities
	puzzleSysTwoB->AddEntityComponents();

	// Update background scene
	UpdateBackgroundScene("NottinghamSquare");

	// Character management, if required
	npcOne.getComponent<SpriteComponent>().SetNewTexture("PeasantOne");
	npcTwo.getComponent<SpriteComponent>().SetToggleDraw(true);
	npcThree.getComponent<SpriteComponent>().SetToggleDraw(true);
	npcOne.getComponent<TransformComponent>().SetNewTransformPos(200.0f, 300.0f);
	npcTwo.getComponent<TransformComponent>().SetNewTransformPos(400.0f, 300.0f);
	npcThree.getComponent<TransformComponent>().SetNewTransformPos(600.0f, 300.0f);

	// Delete old entities and maps, Manage Puzzle
	puzzleSysTwoA->DestroyPuzzlePieces(2, 'A');
	assets->ClearPuzzlePieceMap(2, 'A');
}

void GameMode::Part2SceneC()
{
	std::cout << "\nPart2SceneC()" << std::endl;

	// Output Story Point
	std::cout << "Story Point: Robin tricks The Sheriff into eating with his merry men in Sherwood. He then forces The Sheriff to pay" <<
		" for the feast. This is all for revenge because The Sheriff almost killed Will Stutley." << std::endl;

	// Set previous puzzle to solved
	puzzleSysTwoB->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(2);
	SetStoryScene('C');

	// Add components to entities
	puzzleSysTwoC->AddEntityComponents();

	// Update background scene
	UpdateBackgroundScene("RobinsCamp");

	// Character management, if required
	npcOne.getComponent<SpriteComponent>().SetNewTexture("Stutley");
	npcTwo.getComponent<SpriteComponent>().SetNewTexture("TheTinker");
	npcThree.getComponent<SpriteComponent>().SetToggleDraw(false);
	littleJohn.getComponent<SpriteComponent>().SetToggleDraw(true);
	sheriff.getComponent<SpriteComponent>().SetToggleDraw(true);

	// Delete old entities and maps, Manage Puzzle
	puzzleSysTwoB->DestroyPuzzlePieces(2, 'B');
	assets->ClearPuzzlePieceMap(2, 'B');
}

#pragma endregion Part2Loads

#pragma region Part3Loads

void GameMode::Part3SceneA()
{
	std::cout << "\nPart3SceneA()" << std::endl;

	// Output Story Point
	std::cout << "Story Point: Robin runs into Will Scarlet in Sherwood Forest. Robin assumes Will is wealthy" <<
		" due to his appearance. Robin loses to Will in a fight and then learns Will is his cousin." <<
		" Will is on the run after accidentally killing someone. Robin invites will to join him and his merry men." << std::endl;

	// Set previous puzzle to solved
	puzzleSysTwoC->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(3);
	SetStoryScene('A');

	// Add components to entities
	puzzleSysThreeA->AddEntityComponents();

	// Update background scene
	UpdateBackgroundScene("SherwoodForest3");

	// Character management, if required
	npcTwo.getComponent<SpriteComponent>().SetNewTexture("Scarlet");
	sheriff.getComponent<SpriteComponent>().SetToggleDraw(false);

	// Delete old entities and maps, Manage Puzzle
	puzzleSysTwoC->DestroyPuzzlePieces(2, 'C');
	assets->ClearPuzzlePieceMap(2, 'C');
	puzzleSysTwoA->~PuzzleSystem();
	puzzleSysTwoB->~PuzzleSystem();
	puzzleSysTwoC->~PuzzleSystem();
}

#pragma endregion Part3Loads

#pragma region Part4Loads

void GameMode::Part4SceneA()
{
	std::cout << "Part4SceneA()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin fights Friar Tuck, while looking for him to help with an arranged marriage, "<<
		"in a river. During the fight the learn who the other is and Friar Tuck joins Robin and his merry men." << std::endl;

	// Set previous puzzle to solved
	puzzleSysThreeA->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(4);
	SetStoryScene('A');

	// Add components to entities
	puzzleSysFourA->AddEntityComponents();

	// Update background scene
	UpdateBackgroundScene("RobinFightsLJ");

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
	puzzleSysThreeA->DestroyPuzzlePieces(3, 'A');
	assets->ClearPuzzlePieceMap(3, 'A');
}

void GameMode::Part4SceneB()
{
	std::cout << "Part4SceneB()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin disguised himself as a harp player and infiltrates the wedding. " <<
		"He along with his men are able to help A'Dale. A'Dale joins Robin." << std::endl;

	// Set previous puzzle to solved
	puzzleSysFourA->SetPuzzleStatus(true);

	// Update story scene, and story part when required
	SetStoryPart(4);
	SetStoryScene('B');

	// Add components to entities
	puzzleSysFourB->AddEntityComponents();

	// Update background scene
	UpdateBackgroundScene("TheWedding");

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
	puzzleSysFourA->DestroyPuzzlePieces(4, 'A');
	assets->ClearPuzzlePieceMap(4, 'A');
}

#pragma endregion Part4Loads

#pragma region Part5Loads

void GameMode::Part5SceneA()
{
	std::cout << "Part5SceneA()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

#pragma endregion Part5Loads

#pragma region Part6Loads

void GameMode::Part6SceneA()
{
	std::cout << "Part6SceneA()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

void GameMode::Part6SceneB()
{
	std::cout << "Part6SceneB()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

#pragma endregion Part6Loads

#pragma region Part7Loads

void GameMode::Part7SceneA()
{
	std::cout << "Part7SceneA()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

void GameMode::Part7SceneB()
{
	std::cout << "Part7SceneB()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

#pragma endregion Part7Loads

#pragma region Part8Loads

void GameMode::Part8SceneA()
{
	std::cout << "Part8SceneA()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

void GameMode::Part8SceneB()
{
	std::cout << "Part8SceneB()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

#pragma endregion Part8Loads

#pragma region Part9Loads

void GameMode::Part9SceneA()
{
	std::cout << "Part9SceneA()" << std::endl;

	// Output Story Point
	std::cout << "\nStory Point: Robin attends and wins first archery competion while disguised" << std::endl;

	// Set previous puzzle to solved

	// Update story scene, and story part when required

	// Add components to entities

	// Update background scene

	// Character management, if required

	// Delete old entities and maps, Manage Puzzle
}

#pragma endregion Part9Loads

void GameMode::GameComplete()
{
	std::cout << "GGs Gamer. You completed the game. Now go touch some grass." << std::endl;
}
