// Load an external texture map

#pragma once

#include <string>

class TextureMap
{

public:

	TextureMap();
	TextureMap(const char* mfPath, int mScale, int tSize);
	~TextureMap();

	void LoadTextureMap(std::string path, int sizeX, int sizeY);
	void AddTile(int id, int x, int y);


private:

	const char* mapFilePath;
	int mapScale;
	int tileSize;

};

