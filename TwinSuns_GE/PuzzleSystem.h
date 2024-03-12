// Game Puzzle System Base Class

#pragma once

#include <vector>
#include <string>

class PuzzleSystem
{
private:

	int totalNumPP; // Track if a puzzle piece is the last piece of its puzzle
	int puzzleSysID; // Track number of puzzle pieces, each pp is an entity
	bool puzzleStatus; // Track if puzzle is solved

public:

	// Constructors and Destructors
	PuzzleSystem();
	PuzzleSystem(int totalPP, bool status);
	~PuzzleSystem();

	// Member Functions
	void CreateEntities(); // Use asset manager
	bool CheckPuzzleStatus(); // Check if puzzle requirements have been met
	void SetPuzzleStatus(bool status);
	

	// Puzzle Struct, use to manage all values of individual 
	// Puzzle System Entities
	// Individual puzzle system instances created in Game Class
	struct PuzzleStruct{

		std::string puzzleID;
		int storyPart;
		std::string storyScene;
		bool lastPiece;
		std::vector<int> transform;
		std::vector<std::string> dependencies;
	}puzzlePieceOne, puzzlePieceTwo;

};