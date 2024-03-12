// PuzzleDependencies Class is used to manage puzzle piece dependency
// and the relationship pieces have with other pieces and overall puzzles
// Utilizes a Graph Data Structure, implemented in list form using 
// Unordered map and unordered set


//---------------------------------------
//---------------------------------------
// Class not currently in use

#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

// Make it a child of PuzzleSystem?

class PuzzleDependencies
{
private:

	// Unordered maps for puzzle system dependencies
	std::unordered_map < std::string, std::unordered_set<std::string>> prologueDependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part1_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part2_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part3_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part4_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part5_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part6_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part7_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> part8_Dependencies;
	std::unordered_map < std::string, std::unordered_set<std::string>> epilogueDependencies;

public:

	PuzzleDependencies();
	~PuzzleDependencies();

	// Member functions
	void AddDependencies(int part, std::string puzzlePiece, std::unordered_set<std::string> dependencies);
	

};