#include "AssetManager.h"
#include "ECS/Components.h"


AssetManager::AssetManager(Manager* man) : manager(man)
{

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
