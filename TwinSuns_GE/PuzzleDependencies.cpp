#include "PuzzleDependencies.h"

PuzzleDependencies::PuzzleDependencies()
{}

PuzzleDependencies::~PuzzleDependencies()
{}

void PuzzleDependencies::AddDependencies(int part, std::string puzzlePiece, std::unordered_set<std::string> dependencies)
{
	// switch case to add dependencies to proper map
	switch (part)
	{
	case 0:
		prologueDependencies.emplace(puzzlePiece, dependencies);
		break;

	case 1:
		part1_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 2:
		part2_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 3:
		part3_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 4:
		part4_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 5:
		part5_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 6:
		part6_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 7:
		part7_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 8:
		part8_Dependencies.emplace(puzzlePiece, dependencies);
		break;

	case 9:
		epilogueDependencies.emplace(puzzlePiece, dependencies);

	default:
		break;
	}
}
