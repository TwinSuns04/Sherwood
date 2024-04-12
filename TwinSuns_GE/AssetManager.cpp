#include "AssetManager.h"
#include "ECS/Components.h"


AssetManager::AssetManager(Manager* man) : manager(man)
{
	numPP = 0;
}

AssetManager::~AssetManager()
{
	
}

#pragma region GeneralAssetManagement
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

void AssetManager::AddExpositionElem(std::string id, const char* path)
{
	expositionMap.emplace(id, TextureManager::LoadTexture(path));
}

SDL_Texture* AssetManager::GetExpositionElem(std::string id)
{
	return expositionMap[id];
}

#pragma endregion GeneralAssetManagement

// Create Base Puzzle Piece Entity, minimal components added
void AssetManager::CreateBasePuzzlePiece(std::string id, int part, char scene, int num, bool last)
{
	auto& puzzlePiece(manager->AddEntity());
	puzzlePiece.addComponent<PuzzlePieceComponent>(id, part, scene, num, last);
	puzzlePiece.AddGroup(Game::groupPuzzlePieces);
	puzzlePieceMap.emplace(id, &puzzlePiece);

	switch (part)
	{
	case 0:
		if (scene == 'A')
		{
			puzzleZeroA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleZeroB_IDs.emplace(num, id);
			break;
		}

	case 1:
		if (scene == 'A')
		{
			puzzleOneA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleOneB_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'C')
		{
			puzzleOneC_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'D')
		{
			puzzleOneD_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'E')
		{
			puzzleOneE_IDs.emplace(num, id);
			break;
		}

	case 2:
		if (scene == 'A')
		{
			puzzleTwoA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleTwoB_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'C')
		{
			puzzleTwoC_IDs.emplace(num, id);
			break;
		}

	case 3:
		puzzleThreeA_IDs.emplace(num, id);
		break;

	case 4:
		if (scene == 'A')
		{
			puzzleFourA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleFourB_IDs.emplace(num, id);
			break;
		}

	case 5:
		puzzleFiveA_IDs.emplace(num, id);
		break;

	case 6:
		if (scene == 'A')
		{
			puzzleSixA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleSixB_IDs.emplace(num, id);
			break;
		}

	case 7:
		if (scene == 'A')
		{
			puzzleSevenA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleSevenB_IDs.emplace(num, id);
			break;
		}

	case 8:
		if (scene == 'A')
		{
			puzzleEightA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleEightB_IDs.emplace(num, id);
			break;
		}

	case 9:
		puzzleNineA_IDs.emplace(num, id);
		break;

	default:
		break;
	}
}

void AssetManager::AddEComponents(PuzzleSystem* puzzleSys, std::string id, int num)
{
	std::string spriteID = "";
	std::vector<int> trans;
	std::vector<std::string> depend;

	switch (num)
	{
	case 1:
		spriteID = puzzleSys->puzzlePieceOne.spriteID;
		trans = puzzleSys->puzzlePieceOne.transform;
		depend = puzzleSys->puzzlePieceOne.dependencies;
		break;

	case 2:
		spriteID = puzzleSys->puzzlePieceTwo.spriteID;
		trans = puzzleSys->puzzlePieceTwo.transform;
		depend = puzzleSys->puzzlePieceTwo.dependencies;
		break;

	case 3:
		spriteID = puzzleSys->puzzlePieceThree.spriteID;
		trans = puzzleSys->puzzlePieceThree.transform;
		depend = puzzleSys->puzzlePieceThree.dependencies;
		break;

	case 4:
		spriteID = puzzleSys->puzzlePieceFour.spriteID;
		trans = puzzleSys->puzzlePieceFour.transform;
		depend = puzzleSys->puzzlePieceFour.dependencies;
		break;

	default:
		break;
	}

	GetPuzzlePiece(id)->addComponent<TransformComponent>(static_cast<float>(trans[0]),
		static_cast<float>(trans[1]), trans[2], trans[3], trans[4]);
	GetPuzzlePiece(id)->addComponent<SpriteComponent>(spriteID);
	GetPuzzlePiece(id)->addComponent<CollisionComponent>(id);

	// create and manage dependencies
	for (int i = 0; i < depend.size(); i++)
	{
		GetPuzzlePiece(id)->getComponent<PuzzlePieceComponent>().CreateDependencies(depend[i]);
	}

	std::cout << "AddEComponents Completed for -- " << id << std::endl;
}

// Create individual puzzle pieces and add all components, not in use
void AssetManager::CreatePuzzlePiece(std::string id, int part, char scene, int num,
	bool last, std::vector<int> trans, std::vector<std::string> dependencies)
{
	auto& puzzlePiece(manager->AddEntity());
	puzzlePiece.addComponent<TransformComponent>(static_cast<float>(trans[0]),
		static_cast<float>(trans[1]), trans[2], trans[3], trans[4]);
	puzzlePiece.addComponent<SpriteComponent>(id);
	puzzlePiece.addComponent<CollisionComponent>(id);
	puzzlePiece.addComponent<PuzzlePieceComponent>(id, part, scene, num, last);
	puzzlePiece.AddGroup(Game::groupPuzzlePieces);
	puzzlePieceMap.emplace(id, &puzzlePiece);

	// Create and Manage dependencies
	if (dependencies.size() != 0)
	{
		for (int i = 0; i < dependencies.size(); i++)
		{
			puzzlePiece.getComponent<PuzzlePieceComponent>().CreateDependencies(dependencies[i]);
		}
	}

	switch (part)
	{
	case 0:
		if (scene == 'A')
		{
			puzzleZeroA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleZeroB_IDs.emplace(num, id);
			break;
		}

	case 1:
		if (scene == 'A')
		{
			puzzleOneA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleOneB_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'C')
		{
			puzzleOneC_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'D')
		{
			puzzleOneD_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'E')
		{
			puzzleOneE_IDs.emplace(num, id);
			break;
		}

	case 2:
		if (scene == 'A')
		{
			puzzleTwoA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			std::cout << id << "added to puzzleTwoB_IDs" << std::endl;
			puzzleTwoB_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'C')
		{
			puzzleTwoC_IDs.emplace(num, id);
			break;
		}

	case 3:
		puzzleThreeA_IDs.emplace(num, id);
		break;

	case 4:
		if (scene == 'A')
		{
			puzzleFourA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleFourB_IDs.emplace(num, id);
			break;
		}

	case 5:
		puzzleFiveA_IDs.emplace(num, id);
		break;

	case 6:
		if (scene == 'A')
		{
			puzzleSixA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleSixB_IDs.emplace(num, id);
			break;
		}

	case7:
		if (scene == 'A')
		{
			puzzleSevenA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleSevenB_IDs.emplace(num, id);
			break;
		}

	case 8:
		if (scene == 'A')
		{
			puzzleEightA_IDs.emplace(num, id);
			break;
		}
		else if (scene == 'B')
		{
			puzzleEightB_IDs.emplace(num, id);
			break;
		}

	case 9:
		puzzleNineA_IDs.emplace(num, id);
		break;

	default:
		break;
	}

	std::cout << "\n----Puzzle Piece entity successfully created----" << std::endl;
	std::cout << "Puzzle Piece Addres: " << &puzzlePiece << "\n" << std::endl;

	numPP++;
	std::cout << "Total number of puzzle pieces: " << numPP << std::endl;
	std::cout << "Map size: " << puzzlePieceMap.size() << std::endl;

}

Entity* AssetManager::GetPuzzlePiece(std::string ID)
{
	return puzzlePieceMap[ID];
}

void AssetManager::DestroyPuzzlePieces(int part, char scene)
{
	std::cout << "DestroyPuzzlePieces - Puzzle: " << part << " ----Complete" << std::endl;
	
	switch (part)
	{
	case 0:
		if (scene == 'A')
		{
			for (int i = 1; i < puzzleZeroA_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleZeroA_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleZeroA_IDs[i]);
			}
			puzzleZeroA_IDs.clear();
			break;
		}
		for (int i = 1; i < puzzleZeroB_IDs.size() + 1; i++)
		{
			GetPuzzlePiece(puzzleZeroB_IDs[i])->Destroy();
			puzzlePieceMap.erase(puzzleZeroB_IDs[i]);
		}
		puzzleZeroB_IDs.clear();
		break;

	case 1:
		if (scene == 'A')
		{
			for (int i = 1; i < puzzleOneA_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleOneA_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleOneA_IDs[i]);
			}
			puzzleOneA_IDs.clear();
			break;
		}
		else if (scene == 'B')
		{
			for (int i = 1; i < puzzleOneB_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleOneB_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleOneB_IDs[i]);
			}
			puzzleOneB_IDs.clear();
			break;
		}
		else if (scene == 'C')
		{
			for (int i = 1; i < puzzleOneC_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleOneC_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleOneC_IDs[i]);
			}
			puzzleOneC_IDs.clear();
			break;
		}
		else if (scene == 'D')
		{
			for (int i = 1; i < puzzleOneD_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleOneD_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleOneD_IDs[i]);
			}
			puzzleOneD_IDs.clear();
			break;
		}
		else if (scene == 'E')
		{
			for (int i = 1; i < puzzleOneE_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleOneE_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleOneE_IDs[i]);
			}
			puzzleOneE_IDs.clear();
			break;
		}

	case 2:
		if (scene == 'A')
		{
			for (int i = 1; i < puzzleTwoA_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleTwoA_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleTwoA_IDs[i]);
			}
			puzzleTwoA_IDs.clear();
			break;
		}
		else if (scene == 'B')
		{
			for (int i = 1; i < puzzleTwoB_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleTwoB_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleTwoB_IDs[i]);
			}
			puzzleTwoB_IDs.clear();
			break;
		}
		else if (scene == 'C')
		{
			for (int i = 1; i < puzzleTwoC_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleTwoC_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleTwoC_IDs[i]);
			}
			puzzleTwoC_IDs.clear();
			break;
		}

	case 3:

		for (int i = 1; i < puzzleThreeA_IDs.size() + 1; i++)
		{
			GetPuzzlePiece(puzzleThreeA_IDs[i])->Destroy();
			puzzlePieceMap.erase(puzzleThreeA_IDs[i]);
		}
		puzzleThreeA_IDs.clear();
		break;

	case 4:
		if (scene == 'A')
		{
			for (int i = 1; i < puzzleFourA_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleFourA_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleFourA_IDs[i]);
			}
			puzzleFourA_IDs.clear();
			break;
		}
		else if (scene == 'B')
		{
			for (int i = 1; i < puzzleFourB_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleFourB_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleFourB_IDs[i]);
			}
			puzzleFourB_IDs.clear();
			break;
		}

	case 5:
		for (int i = 1; i < puzzleFiveA_IDs.size() + 1; i++)
		{
			GetPuzzlePiece(puzzleFiveA_IDs[i])->Destroy();
			puzzlePieceMap.erase(puzzleFiveA_IDs[i]);
		}
		puzzleFiveA_IDs.clear();
		break;

	case 6:
		if (scene == 'A')
		{
			for (int i = 1; i < puzzleSixA_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleSixA_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleSixA_IDs[i]);
			}
			puzzleSixA_IDs.clear();
			break;
		}
		else if (scene == 'B')
		{
			for (int i = 1; i < puzzleSixB_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleSixB_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleSixB_IDs[i]);
			}
			puzzleSixB_IDs.clear();
			break;
		}

	case 7:
		if (scene == 'A')
		{
			for (int i = 1; i < puzzleSevenA_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleSevenA_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleSevenA_IDs[i]);
			}
			puzzleSevenA_IDs.clear();
			break;
		}
		else if (scene == 'B')
		{
			for (int i = 1; i < puzzleSevenB_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleSevenB_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleSevenB_IDs[i]);
			}
			puzzleSevenB_IDs.clear();
			break;
		}

	case 8:
		if (scene == 'A')
		{
			for (int i = 1; i < puzzleEightA_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleEightA_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleEightA_IDs[i]);
			}
			puzzleEightA_IDs.clear();
			break;
		}
		else if (scene == 'B')
		{
			for (int i = 1; i < puzzleEightB_IDs.size() + 1; i++)
			{
				GetPuzzlePiece(puzzleEightB_IDs[i])->Destroy();
				puzzlePieceMap.erase(puzzleEightB_IDs[i]);
			}
			puzzleEightB_IDs.clear();
			break;
		}

	case 9:
		for (int i = 1; i < puzzleNineA_IDs.size() + 1; i++)
		{
			GetPuzzlePiece(puzzleNineA_IDs[i])->Destroy();
			puzzlePieceMap.erase(puzzleNineA_IDs[i]);
		}
		puzzleNineA_IDs.clear();
		break;

	default:
		break;
	}
}

bool AssetManager::ClearPuzzlePieceMap(int part, char scene)
{
	std::unordered_map<int, std::string> tempMap = *ClearPuzzleSysPieceMap(part, scene);
	std::string tempString = "";

	for (int i = 1; i < tempMap.size() + 1; i++)
	{
		tempString = tempMap[i];

		puzzlePieceMap.erase(tempString);

	}

	tempMap.clear();
	if (tempMap.empty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

std::unordered_map<int, std::string>* AssetManager::ClearPuzzleSysPieceMap(int part, char scene)
{
	std::unordered_map<int, std::string>* tempMap1{};


	switch (part)
	{
	case 0:
		if (scene == 'A')
		{
			tempMap1 = &puzzleZeroA_IDs;
			break;
		}
		else if (scene == 'B')
		{
			tempMap1 = &puzzleZeroB_IDs;
			break;
		}

	case 1:
		if (scene == 'A')
		{
			tempMap1 = &puzzleOneA_IDs;
			break;
		}
		else if (scene == 'B')
		{
			tempMap1 = &puzzleOneB_IDs;
			break;
		}
		else if (scene == 'C')
		{
			tempMap1 = &puzzleOneC_IDs;
			break;
		}
		else if (scene == 'D')
		{
			tempMap1 = &puzzleOneD_IDs;
			break;
		}
		else if (scene == 'E')
		{
			tempMap1 = &puzzleOneE_IDs;
			break;
		}

	case 2:
		if (scene == 'A')
		{
			tempMap1 = &puzzleTwoA_IDs;
			break;
		}
		else if (scene == 'B')
		{
			tempMap1 = &puzzleTwoB_IDs;
			break;
		}
		else if (scene == 'C')
		{
			tempMap1 = &puzzleTwoC_IDs;
			break;
		}

	case 3:
		tempMap1 = &puzzleThreeA_IDs;
		break;

	case 4:
		if (scene == 'A')
		{
			tempMap1 = &puzzleFourA_IDs;
			break;
		}
		else if (scene == 'B')
		{
			tempMap1 = &puzzleFourB_IDs;
			break;
		}

	case 5:
		tempMap1 = &puzzleFiveA_IDs;
		break;

	case 6:
		if (scene == 'A')
		{
			tempMap1 = &puzzleSixA_IDs;
			break;
		}
		else if (scene == 'B')
		{
			tempMap1 = &puzzleSixB_IDs;
			break;
		}

	case 7:
		if (scene == 'A')
		{
			tempMap1 = &puzzleSevenA_IDs;
			break;
		}
		else if (scene == 'B')
		{
			tempMap1 = &puzzleSevenB_IDs;
			break;
		}

	case 8:
		if (scene == 'A')
		{
			tempMap1 = &puzzleEightA_IDs;
			break;
		}
		else if (scene == 'B')
		{
			tempMap1 = &puzzleEightB_IDs;
			break;
		}

	case 9:
		tempMap1 = &puzzleNineA_IDs;
		break;

	default:
		break;
	}

	return tempMap1;
}


#pragma region PuzzleLoads
void AssetManager::PuzzleZero_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleZeroA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleZeroA_IDs[i], i);
	}
}

void AssetManager::PuzzleZero_BLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleZeroB_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleZeroB_IDs[i], i);
	}
}

void AssetManager::PuzzleOne_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleOneA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleOneA_IDs[i], i);
	}
}

void AssetManager::PuzzleOne_BLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleOneB_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleOneB_IDs[i], i);
	}
}

void AssetManager::PuzzleOne_CLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleOneC_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleOneC_IDs[i], i);
	}
}

void AssetManager::PuzzleOne_DLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleOneD_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleOneD_IDs[i], i);
	}
}

void AssetManager::PuzzleOne_ELoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleOneE_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleOneE_IDs[i], i);
	}
}

void AssetManager::PuzzleTwo_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleTwoA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleTwoA_IDs[i], i);
	}
}

void AssetManager::PuzzleTwo_BLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleTwoB_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleTwoB_IDs[i], i);
	}
}

void AssetManager::PuzzleTwo_CLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleTwoC_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleTwoC_IDs[i], i);
	}
}

void AssetManager::PuzzleThree_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleThreeA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleThreeA_IDs[i], i);
	}
}

void AssetManager::PuzzleFour_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleFourA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleFourA_IDs[i], i);
	}
}

void AssetManager::PuzzleFour_BLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleFourB_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleFourB_IDs[i], i);
	}
}

void AssetManager::PuzzleFive_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleFiveA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleFiveA_IDs[i], i);
	}
}

void AssetManager::PuzzleSix_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleSixA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleSixA_IDs[i], i);
	}
}

void AssetManager::PuzzleSix_BLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleSixB_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleSixB_IDs[i], i);
	}
}

void AssetManager::PuzzleSeven_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleSevenA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleSevenA_IDs[i], i);
	}
}

void AssetManager::PuzzleSeven_BLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleSevenB_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleSevenB_IDs[i], i);
	}
}

void AssetManager::PuzzleEight_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleEightA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleEightA_IDs[i], i);
	}
}

void AssetManager::PuzzleEight_BLoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleEightB_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleEightB_IDs[i], i);
	}
}

void AssetManager::PuzzleNine_ALoad(PuzzleSystem* puzzleSys)
{
	for (int i = 1; i < puzzleNineA_IDs.size() + 1; i++)
	{
		AddEComponents(puzzleSys, puzzleNineA_IDs[i], i);
	}
}
#pragma endregion PuzzleLoads

int AssetManager::GetMapSize()
{
	return puzzleTwoB_IDs.size();
}

void AssetManager::GetMapElements()
{
	for (int i = 1; i <= puzzleTwoB_IDs.size(); i++)
	{
		std::cout << "Element " << i << "s id: " << puzzleTwoB_IDs[i] << std::endl;
	}
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
