// Manages assets
// Creates textures and builds game objects

#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL_ttf.h"
#include "PuzzleSystem.h"
#include <unordered_map>

class AssetManager
{

public:

	AssetManager(Manager* man);
	~AssetManager();

	// Texture Management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	// Font Management
	void AddFont(std::string id, std::string path, int fontSize);
	TTF_Font* GetFont(std::string id);

	// Exposition Management
	void AddExpositionElem(std::string id, const char* path);
	SDL_Texture* GetExpositionElem(std::string id);

	// Functions
	void CreateBasePuzzlePiece(std::string id, int part, char scene, int num, bool last);
	void AddEComponents(PuzzleSystem *puzzleSys, std::string id, int num);
	void CreatePuzzlePiece(std::string id, int part, char scene, int num,
		bool last, std::vector<int> trans, std::vector<std::string> dependencies);

	Entity* GetPuzzlePiece(std::string ID);

	void DestroyPuzzlePieces(int part, char scene);
	bool ClearPuzzlePieceMap(int part, char scene);
	std::unordered_map<int, std::string>* ClearPuzzleSysPieceMap(int part, char scene);

	int GetMapSize(); // For Debugging
	void GetMapElements(); // For Debugging

	// Scene loaders
	void PuzzleZero_ALoad(PuzzleSystem *puzzleSys);
	void PuzzleZero_BLoad(PuzzleSystem* puzzleSys);

	void PuzzleOne_ALoad(PuzzleSystem* puzzleSys);
	void PuzzleOne_BLoad(PuzzleSystem* puzzleSys);
	void PuzzleOne_CLoad(PuzzleSystem* puzzleSys);
	void PuzzleOne_DLoad(PuzzleSystem* puzzleSys);
	void PuzzleOne_ELoad(PuzzleSystem* puzzleSys);

	void PuzzleTwo_ALoad(PuzzleSystem* puzzleSys);
	void PuzzleTwo_BLoad(PuzzleSystem* puzzleSys);
	void PuzzleTwo_CLoad(PuzzleSystem* puzzleSys);

	void PuzzleThree_ALoad(PuzzleSystem* puzzleSys);

	void PuzzleFour_ALoad(PuzzleSystem* puzzleSys);
	void PuzzleFour_BLoad(PuzzleSystem* puzzleSys);

	void PuzzleFive_ALoad(PuzzleSystem* puzzleSys);

	void PuzzleSix_ALoad(PuzzleSystem* puzzleSys);
	void PuzzleSix_BLoad(PuzzleSystem* puzzleSys);

	void PuzzleSeven_ALoad(PuzzleSystem* puzzleSys);
	void PuzzleSeven_BLoad(PuzzleSystem* puzzleSys);

	void PuzzleEight_ALoad(PuzzleSystem* puzzleSys);
	void PuzzleEight_BLoad(PuzzleSystem* puzzleSys);

	void PuzzleNine_ALoad(PuzzleSystem* puzzleSys);

private:

	// vars
	int numPP;
	int numPuzzlePieces;

	// local manager
	Manager* manager;

	// map to manage textures, in format of map <key, mappedVal>
	std::map<std::string, SDL_Texture*> texturesMap;

	// map to manage fonts
	std::map<std::string, TTF_Font*> fontsMap;

	 // map to manage exposition
	std::map<std::string, SDL_Texture*> expositionMap;

	// maps to manage puzzle pieces entity
	std::map<std::string, Entity*> puzzlePieceMap;

	// unordered maps to manage puzzlepiece ids for specific systems
	std::unordered_map<int, std::string> puzzleZeroA_IDs;
	std::unordered_map<int, std::string> puzzleZeroB_IDs;

	std::unordered_map<int, std::string> puzzleOneA_IDs;
	std::unordered_map<int, std::string> puzzleOneB_IDs;
	std::unordered_map<int, std::string> puzzleOneC_IDs;
	std::unordered_map<int, std::string> puzzleOneD_IDs;
	std::unordered_map<int, std::string> puzzleOneE_IDs;

	std::unordered_map<int, std::string> puzzleTwoA_IDs;
	std::unordered_map<int, std::string> puzzleTwoB_IDs;
	std::unordered_map<int, std::string> puzzleTwoC_IDs;

	std::unordered_map<int, std::string> puzzleThreeA_IDs;

	std::unordered_map<int, std::string> puzzleFourA_IDs;
	std::unordered_map<int, std::string> puzzleFourB_IDs;

	std::unordered_map<int, std::string> puzzleFiveA_IDs;

	std::unordered_map<int, std::string> puzzleSixA_IDs;
	std::unordered_map<int, std::string> puzzleSixB_IDs;

	std::unordered_map<int, std::string> puzzleSevenA_IDs;
	std::unordered_map<int, std::string> puzzleSevenB_IDs;

	std::unordered_map<int, std::string> puzzleEightA_IDs;
	std::unordered_map<int, std::string> puzzleEightB_IDs;

	std::unordered_map<int, std::string> puzzleNineA_IDs;

};
