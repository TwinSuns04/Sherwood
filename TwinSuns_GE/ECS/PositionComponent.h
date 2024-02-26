// No longer in use
// Use transform component

#pragma once

#include "Components.h"

class PositionComponent : public Component
{

private:

	int xPos;
	int yPos;

public:

	PositionComponent()
	{
		xPos = 0;
		yPos = 0;
	}

	PositionComponent(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

	// override Component class Update() function
	void Update() override
	{
		xPos++;
		yPos++;
	}

	int GetXPosition()
	{
		return xPos;
	}

	int GetYPosition()
	{
		return yPos;
	}



	void SetPositions(int x, int y)
	{
		xPos = x;
		yPos = y;
	}

};