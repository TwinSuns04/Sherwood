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

	// vars
	bool clickStatus;
	bool bUsed;

	std::vector<std::string> dependentVector;

	// try list if vector is insufficient
	std::list <std::string> dependentList;

public:

	// vars
	std::string pieceName;

	PuzzlePieceComponent()
	{}

	PuzzlePieceComponent(std::string id)
	{
		pieceName = id;
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

		std::cout << "bUsed: " << GetbUsed() << std::endl;
		
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

	void CreateDependencies(std::string dependentID)
	{
		std::cout << "CreateDependencies() exec" << std::endl;

		dependentVector.emplace_back(dependentID);
	}

	// Check if dependent puzzle pieces have been used properly
	// If yes, update this->puzzlePiece bUsed = true
	bool CheckDependencies()
	{
		std::cout << "CheckDependencies() exec" << std::endl;
		std::cout << "PuzzlePieceID: " << pieceName << "\n" << std::endl;

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