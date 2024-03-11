#include "AssetManager.h"
#include "ECS/Components.h"


AssetManager::AssetManager(Manager* man) : manager(man)
{
	numPP = 0;
}

AssetManager::~AssetManager()
{
	
}

void AssetManager::AddTexture(std::string id, const char* path)
{
	texturesMap.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetTexture(std::string id)
{
	return texturesMap[id];
}

void AssetManager::AddFont(std::string id, std::string path, int fontSize)
{
	fontsMap.emplace(id, TTF_OpenFont(path.c_str(), fontSize));
}

TTF_Font* AssetManager::GetFont(std::string id)
{
	return fontsMap[id];
}

// Create individual puzzle pieces
void AssetManager::CreatePuzzlePiece(std::string id, std::vector<int> trans,
	std::vector<std::string> dependencies)
{
	numPP++;
	auto& puzzlePiece(manager->AddEntity());
	puzzlePiece.addComponent<TransformComponent>(static_cast<float> (trans[0]), 
		static_cast<float> (trans[1]), trans[2], trans[3], trans[4]);
	puzzlePiece.addComponent<SpriteComponent>(id);
	puzzlePiece.addComponent<CollisionComponent>(id);
	puzzlePiece.addComponent<PuzzlePieceComponent>(id);
	puzzlePiece.AddGroup(Game::groupPuzzlePieces);
	puzzlePieceMap.emplace(id, &puzzlePiece);

	// Manage puzzlePiece dependcies
	if (dependencies.size() != 0)
	{
		for (int i = 0; i < dependencies.size(); i++)
		{
			puzzlePiece.getComponent<PuzzlePieceComponent>().CreateDependencies(dependencies[i]);
		}
	}

}

Entity* AssetManager::GetPuzzlePiece(std::string ID)
{
	return puzzlePieceMap[ID];
}

// Canyon Run Code
/*
void AssetManager::CreateProjectile(Vector2D crosshairPos, Vector2D laserPos, int range, int speed, std::string id)
{
	auto& projectile(manager->AddEntity());
	projectile.addComponent<TransformComponent>(laserPos.x, laserPos.y, 4, 44, 2);
	projectile.addComponent<SpriteComponent>(id);
	projectile.addComponent<ProjectileComponent>(range, speed, crosshairPos);
	projectile.AddGroup(Game::groupProjectiles);
}

void AssetManager::SpawnEnemyWomp(Vector2D pos, Vector2D vel, int speed, std::string id)
{
	auto& womp(manager->AddEntity());
	womp.addComponent<TransformComponent>(pos.x, pos.y, 32, 32, 2);
	womp.addComponent<SpriteComponent>(id);
	womp.addComponent<CollisionComponent>("womp");
	womp.addComponent<HealthComponent>(100, 100, true);
	womp.addComponent<ObjectController>(speed);
	womp.AddGroup(Game::groupEnemies);
}
*/
