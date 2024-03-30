// Puzzle Piece Component
// Used to manage individual puzzle pieces and their corresponding vars and info

#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"
//#include "../AssetManager.h"
#include <vector>
#include <list>

class PuzzlePieceComponent : public Component
{
private:

	GameMode* gameMode = new GameMode();

	// vars
	bool clickStatus;
	bool bUsed;
	int storyPart;
	char storyScene;
	int numID;

	std::vector<std::string> dependentVector;

	// try list if vector is insufficient
	std::list <std::string> dependentList;

public:

	// vars
	std::string pieceName;
	bool lastPiece; // Track if a puzzle piece is the last piece of its puzzle system

	PuzzlePieceComponent()
	{}

	PuzzlePieceComponent(std::string id)
	{
		pieceName = id;
		lastPiece = false; // if not specified, piece is assumed to not be final piece
	}

	PuzzlePieceComponent(std::string id, int part, char scene, int num, bool last)
	{
		pieceName = id;
		storyPart = part;
		storyScene = scene;
		numID = num;
		lastPiece = last;
		dependentVector.clear();
	}

	~PuzzlePieceComponent()
	{}

	void Init() override
	{
		clickStatus = false;
		bUsed = false;
	}


	void SetClickStatus(bool click)
	{
		clickStatus = click;

		// If puzzle piece has not been used, check dependencies
		if (!GetbUsed())
		{
			SetbUsed(CheckDependencies());
		}

		//std::cout << "bUsed: " << GetbUsed() << std::endl;

		// If the puzzle piece has been properly used
		// and is the last piece
		if (bUsed && lastPiece)
		{
			//std::cout << "PuzzlePiece used and is last piece" << "\n" << std::endl;

			// call appropriate function in GameMode class, pass part and scene
			gameMode->ManageStoryPart(storyPart, storyScene);
		}

	}

	bool GetClickStatus()
	{
		return clickStatus;
	}

	void SetbUsed(bool used)
	{
		bUsed = used;
	}

	bool GetbUsed()
	{
		return bUsed;
	}

	void SetNumID(int num)
	{
		numID = num;
	}

	int GetNumID()
	{
		return numID;
	}

	void SetLastPiece(bool last)
	{
		lastPiece = last;
	}

	bool GetLastPiece()
	{
		return lastPiece;
	}

	void SetStoryScene(char scene)
	{
		storyScene = scene;
	}

	char GetStoryScene()
	{
		return storyScene;
	}

	void CreateDependencies(std::string dependentID)
	{
		//std::cout << "CreateDependencies() exec" << std::endl;

		dependentVector.emplace_back(dependentID);
	}

	// Check if dependent puzzle pieces have been used properly
	// If yes, update this->puzzlePiece bUsed = true
	bool CheckDependencies()
	{
		//std::cout << "CheckDependencies() exec" << std::endl;
		std::cout << "PuzzlePieceID: " << pieceName << std::endl;

		// Check if puzzlePiece is dependent
		if (dependentVector.size() != 0)
		{
			// Need to check bUsed for all dependencies, use asset manager
			// Iterate through list
			for (int i = 0; i < dependentVector.size(); i++)
			{
				// check value of bUsed for each dependent puzzle piece
				if (Game::assets->GetPuzzlePiece(dependentVector[i])->getComponent<PuzzlePieceComponent>().GetbUsed() == false)
				{
					return false;
				}
			}
		}

		// Either puzzle piece has is not dependent or all dependencies have been met
		return true;
	}


};