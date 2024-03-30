// Game Puzzle System Base Class

#include "PuzzleSystem.h"
#include "AssetManager.h"

PuzzleSystem::PuzzleSystem()
{
	puzzleStatus = false;
}

PuzzleSystem::PuzzleSystem(int part, char scene)
{
	puzzleStatus = false;
	puzzlePart = part;
	puzzleScene = scene;
}

PuzzleSystem::PuzzleSystem(int totalPP, bool status)
{}

PuzzleSystem::~PuzzleSystem()
{}

void PuzzleSystem::CreateBaseEntity(int numPP)
{
	std::cout << "CreateBaseEntity()" << std::endl;

	switch (numPP)
	{
	case 1:
		Game::assets->CreateBasePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece);
		break;

	case 2:
		Game::assets->CreateBasePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece);
		Game::assets->CreateBasePuzzlePiece(puzzlePieceTwo.puzzleID, puzzlePieceTwo.storyPart,
			puzzlePieceTwo.storyScene, puzzlePieceTwo.puzzlePieceNum, puzzlePieceTwo.lastPiece);
		break;

	case 3:
		Game::assets->CreateBasePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece);
		Game::assets->CreateBasePuzzlePiece(puzzlePieceTwo.puzzleID, puzzlePieceTwo.storyPart,
			puzzlePieceTwo.storyScene, puzzlePieceTwo.puzzlePieceNum, puzzlePieceTwo.lastPiece);
		Game::assets->CreateBasePuzzlePiece(puzzlePieceThree.puzzleID, puzzlePieceThree.storyPart,
			puzzlePieceThree.storyScene, puzzlePieceThree.puzzlePieceNum, puzzlePieceThree.lastPiece);
		break;

	case 4:
		Game::assets->CreateBasePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece);
		Game::assets->CreateBasePuzzlePiece(puzzlePieceTwo.puzzleID, puzzlePieceTwo.storyPart,
			puzzlePieceTwo.storyScene, puzzlePieceTwo.puzzlePieceNum, puzzlePieceTwo.lastPiece);
		Game::assets->CreateBasePuzzlePiece(puzzlePieceThree.puzzleID, puzzlePieceThree.storyPart,
			puzzlePieceThree.storyScene, puzzlePieceThree.puzzlePieceNum, puzzlePieceThree.lastPiece);
		Game::assets->CreateBasePuzzlePiece(puzzlePieceFour.puzzleID, puzzlePieceFour.storyPart,
			puzzlePieceFour.storyScene, puzzlePieceFour.puzzlePieceNum, puzzlePieceFour.lastPiece);
		break;

	default:
		break;
	}
}

void PuzzleSystem::AddEntityComponents()
{

	char scene = this->puzzleScene;

	switch (this->GetPuzzlePart())
	{
	case 0:
		if (scene == 'A')
		{
			Game::assets->PuzzleZero_ALoad(this);
			break;
		}
		else if (scene == 'B')
		{
			Game::assets->PuzzleZero_BLoad(this);
			break;
		}
		break;

	case 1:
		if (scene == 'A')
		{
			Game::assets->PuzzleOne_ALoad(this);
			break;
		}
		else if (scene == 'B')
		{
			Game::assets->PuzzleOne_BLoad(this);
			break;
		}
		else if (scene == 'C')
		{
			Game::assets->PuzzleOne_CLoad(this);
			break;
		}
		else if (scene == 'D')
		{
			Game::assets->PuzzleOne_DLoad(this);
			break;
		}
		else if (scene == 'E')
		{
			Game::assets->PuzzleOne_ELoad(this);
			break;
		}
		break;

	case 2:
		if (scene == 'A')
		{
			Game::assets->PuzzleTwo_ALoad(this);
			break;
		}
		else if (scene == 'B')
		{
			Game::assets->PuzzleTwo_BLoad(this);
			break;
		}
		else if (scene == 'C')
		{
			Game::assets->PuzzleTwo_CLoad(this);
			break;
		}
		break;

	case 3:
		if (scene == 'A')
		{
			Game::assets->PuzzleThree_ALoad(this);
			break;
		}
		break;

	case 4:
		if (scene == 'A')
		{
			Game::assets->PuzzleFour_ALoad(this);
			break;
		}
		else if (scene == 'B')
		{
			Game::assets->PuzzleFour_BLoad(this);
			break;
		}
		break;

	case 5:
		if (scene == 'A')
		{
			Game::assets->PuzzleFive_ALoad(this);
			break;
		}
		break;

	case 6:
		if (scene == 'A')
		{
			Game::assets->PuzzleSix_ALoad(this);
			break;
		}
		else if (scene == 'B')
		{
			Game::assets->PuzzleSix_BLoad(this);
			break;
		}
		break;

	case 7:
		if (scene == 'A')
		{
			Game::assets->PuzzleSeven_ALoad(this);
			break;
		}
		else if (scene == 'B')
		{
			Game::assets->PuzzleSeven_BLoad(this);
			break;
		}
		break;

	case 8:
		if (scene == 'A')
		{
			Game::assets->PuzzleEight_ALoad(this);
			break;
		}
		else if (scene == 'B')
		{
			Game::assets->PuzzleEight_BLoad(this);
			break;
		}
		break;

	case 9:
		if (scene == 'A')
		{
			Game::assets->PuzzleNine_ALoad(this);
			break;
		}
		break;

	default:
		break;
	}
}

void PuzzleSystem::CreateEntities(int numPP)
{
	std::cout << "CreateEntities()" << std::endl;

	switch (numPP)
	{
	case 1:
		Game::assets->CreatePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece,
			puzzlePieceOne.transform, puzzlePieceOne.dependencies);
		break;

	case 2:
		Game::assets->CreatePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece,
			puzzlePieceOne.transform, puzzlePieceOne.dependencies);

		Game::assets->CreatePuzzlePiece(puzzlePieceTwo.puzzleID, puzzlePieceTwo.storyPart,
			puzzlePieceTwo.storyScene, puzzlePieceTwo.puzzlePieceNum, puzzlePieceTwo.lastPiece,
			puzzlePieceTwo.transform, puzzlePieceTwo.dependencies);
		break;

	case 3:
		Game::assets->CreatePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece,
			puzzlePieceOne.transform, puzzlePieceOne.dependencies);

		Game::assets->CreatePuzzlePiece(puzzlePieceTwo.puzzleID, puzzlePieceTwo.storyPart,
			puzzlePieceTwo.storyScene, puzzlePieceTwo.puzzlePieceNum, puzzlePieceTwo.lastPiece,
			puzzlePieceTwo.transform, puzzlePieceTwo.dependencies);

		Game::assets->CreatePuzzlePiece(puzzlePieceThree.puzzleID, puzzlePieceThree.storyPart,
			puzzlePieceThree.storyScene, puzzlePieceThree.puzzlePieceNum, puzzlePieceThree.lastPiece,
			puzzlePieceThree.transform, puzzlePieceThree.dependencies);
		break;

	case 4:
		Game::assets->CreatePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.storyPart,
			puzzlePieceOne.storyScene, puzzlePieceOne.puzzlePieceNum, puzzlePieceOne.lastPiece,
			puzzlePieceOne.transform, puzzlePieceOne.dependencies);

		Game::assets->CreatePuzzlePiece(puzzlePieceTwo.puzzleID, puzzlePieceTwo.storyPart,
			puzzlePieceTwo.storyScene, puzzlePieceTwo.puzzlePieceNum, puzzlePieceTwo.lastPiece,
			puzzlePieceTwo.transform, puzzlePieceTwo.dependencies);

		Game::assets->CreatePuzzlePiece(puzzlePieceThree.puzzleID, puzzlePieceThree.storyPart,
			puzzlePieceThree.storyScene, puzzlePieceThree.puzzlePieceNum, puzzlePieceThree.lastPiece,
			puzzlePieceThree.transform, puzzlePieceThree.dependencies);

		Game::assets->CreatePuzzlePiece(puzzlePieceFour.puzzleID, puzzlePieceFour.storyPart,
			puzzlePieceFour.storyScene, puzzlePieceFour.puzzlePieceNum, puzzlePieceFour.lastPiece,
			puzzlePieceFour.transform, puzzlePieceFour.dependencies);
		break;

	default:
		break;
	}
}

bool PuzzleSystem::CheckPuzzleStatus()
{
	return puzzleStatus;
}

void PuzzleSystem::SetPuzzleStatus(bool status)
{
	puzzleStatus = status;
}

void PuzzleSystem::SetPuzzlePart(int part)
{
	puzzlePart = part;
}

int PuzzleSystem::GetPuzzlePart()
{
	return puzzlePart;
}

void PuzzleSystem::SetPuzzleScene(char scene)
{
	puzzleScene = scene;
}

char PuzzleSystem::GetPuzzleScene()
{
	return puzzleScene;
}

void PuzzleSystem::DestroyPuzzlePieces(int part, char scene)
{
	Game::assets->DestroyPuzzlePieces(part, scene);
}

void PuzzleSystem::ClearPuzzlePieceMap(int part, char scene)
{
	Game::assets->ClearPuzzlePieceMap(part, scene);
}
