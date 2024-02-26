#include "TextureMap.h"
#include "Game.h"
#include <fstream>
#include "ECS/ECS.h"
#include "ECS/Components.h"

extern Manager manager;

TextureMap::TextureMap()
{

}

TextureMap::TextureMap(const char* mfPath, int mScale, int tSize)
{
	mapFilePath = mfPath;
	mapScale = mScale;
	tileSize = tSize;
}

TextureMap::~TextureMap()
{
	
}

void TextureMap::LoadTextureMap(std::string path, int sizeX, int sizeY)
{

	/*
	char tile;
	std::fstream mapFile;
	
	mapFile.open(path);

	// Future map implementation
	int srcX, srcY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			/*  future map implementation
			srcY = atoi(&tile);
			mapFile.get(tile);
			srcX = atoi(&tile);
			Game::AddTileFuture(srcX, srcY, x * 32, y * 32);
			*/

			// create collider
			/*
			if (tile == '1')
			{
				auto& tileColl(manager.AddEntity());
				tileColl.addComponent<CollisionComponent>("border",
					x * (tileSize * mapScale), y * (tileSize * mapScale), tileSize * mapScale);
				tileColl.AddGroup(Game::groupColliders);
			}
			*/
	/*
			AddTile(atoi(&tile), x * (tileSize * mapScale), y * (tileSize * mapScale));
			mapFile.ignore();
		}
	}

	mapFile.close();
	*/
}

void TextureMap::AddTile(int id, int x, int y)
{
	auto& tile(manager.AddEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	//tile.AddGroup(Game::groupMap);
}
