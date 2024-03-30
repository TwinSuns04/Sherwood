// Game Puzzle System Base Class

#pragma once

#include <vector>
#include <string>

class PuzzleSystem
{
private:

	int totalNumPP; // Track if a puzzle piece is the last piece of its puzzle
	int puzzleSysID; // Track number of puzzle pieces, each pp is an entity
	int puzzlePart;
	char puzzleScene;
	bool puzzleStatus; // Track if puzzle is solved

public:

	// Constructors and Destructors
	PuzzleSystem();
	PuzzleSystem(int part, char scene);
	PuzzleSystem(int totalPP, bool status);
	~PuzzleSystem();

	// Member Functions
	void CreateBaseEntity(int numPP);
	void CreateEntities(int numPP); // Use asset manager
	void AddEntityComponents();
	bool CheckPuzzleStatus(); // Check if puzzle requirements have been met
	void SetPuzzleStatus(bool status);
	void SetPuzzlePart(int part);
	int GetPuzzlePart();
	void SetPuzzleScene(char scene);
	char GetPuzzleScene();
	void DestroyPuzzlePieces(int part, char scene);
	void ClearPuzzlePieceMap(int part, char scene);


	

	// Puzzle Struct, use to manage all values of individual 
	// Puzzle System Entities
	// Individual puzzle system instances created in Game Class
	struct PuzzleStruct{

		std::string puzzleID;
		int storyPart;
		char storyScene;
		int puzzlePieceNum;
		bool lastPiece;
		std::string spriteID;
		std::vector<int> transform;
		std::vector<std::string> dependencies;
	}puzzlePieceOne, puzzlePieceTwo, puzzlePieceThree,
		puzzlePieceFour;

};