// Manages assets
// Creates textures and builds game objects

#pragma once
#include <map>
#include <string>
#include "TextureManager.h"
#include "Vector2D.h"
#include "ECS/ECS.h"

class AssetManager
{

public:

	AssetManager(Manager* man);
	~AssetManager();

	// Texture Management
	void AddTexture(std::string id, const char* path);
	SDL_Texture* GetTexture(std::string id);

	// Functions
	

private:

	// local manager
	Manager* manager;

	// map to manage textures, in format of map <key, mappedVal>
	std::map<std::string, SDL_Texture*> texturesMap;

};
