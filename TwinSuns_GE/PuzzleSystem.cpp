// Game Puzzle System Base Class

#include "PuzzleSystem.h"
#include "AssetManager.h"

PuzzleSystem::PuzzleSystem()
{
	puzzleStatus = false;
}

PuzzleSystem::PuzzleSystem(bool status)
{
	puzzleStatus = status;
}

PuzzleSystem::~PuzzleSystem()
{}

void PuzzleSystem::CreateEntities()
{
	Game::assets->CreatePuzzlePiece(puzzlePieceOne.puzzleID, puzzlePieceOne.transform, puzzlePieceOne.dependencies);
	Game::assets->CreatePuzzlePiece(puzzlePieceTwo.puzzleID, puzzlePieceTwo.transform, puzzlePieceTwo.dependencies);
}

bool PuzzleSystem::CheckPuzzleStatus()
{
	return puzzleStatus;
}

void PuzzleSystem::SetPuzzleStatus(bool status)
{
	puzzleStatus = status;
}
