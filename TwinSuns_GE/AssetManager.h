// Manages assets
// Creates textures and builds game objects

#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"
#include "SDL_ttf.h"

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

	// Functions
	void CreatePuzzlePiece(std::string id, std::vector<int> trans,
		std::vector<std::string> dependencies);
	Entity* GetPuzzlePiece(std::string ID);

private:

	// vars
	int numPP;

	// local manager
	Manager* manager;

	// map to manage textures, in format of map <key, mappedVal>
	std::map<std::string, SDL_Texture*> texturesMap;

	// map to manage fonts
	std::map<std::string, TTF_Font*> fontsMap;

	// map to manage puzzle pieces
	std::map<std::string, Entity*> puzzlePieceMap;

};
