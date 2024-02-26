// Implementation for Advanced Timer class

#include "AdvancedTimer.h"
#include <iostream>

AdvancedTimer::AdvancedTimer()
{
	// Init vars

	isStarted = false;
	isPaused = false;
	startTicks = 0;
	pauseTicks = 0;
	AdvancedTimer::mainTicks = 0;
}

void AdvancedTimer::TimerStart()
{
	/*
	
	std::cout << "AdvancedTimer::TimerStart Executed" << std::endl;
	std::cout << "Pre mainTicks: " << mainTicks << std::endl;
	std::cout << "Pre startTicks: " << startTicks << std::endl;
	*/
	isStarted = true;
	isPaused = false;
	mainTicks = 0;
	startTicks = mainTicks;
	isPaused = 0;

	/*
	std::cout << "Post mainTicks: " << mainTicks << std::endl;
	std::cout << "Post startTicks: " << startTicks << std::endl;
	*/
}

void AdvancedTimer::TimerStop()
{
	/*
	std::cout << "AdvancedTimer::TimerStop Executed" << std::endl;
	std::cout << "Stop() mainTicks: " << mainTicks << std::endl;
	std::cout << "Stop() startTicks: " << startTicks << std::endl;
	*/
	isStarted = false;
	isPaused = false;
	startTicks = 0;
	pauseTicks = 0;
}

void AdvancedTimer::TimerPause()
{
	if ((isStarted) && (!isPaused))
	{
		isPaused = true;
		pauseTicks = mainTicks - startTicks;
		startTicks = 0;
	}
}

void AdvancedTimer::TimerUnpause()
{
	if ((isStarted) && (isPaused))
	{
		isPaused = false;
		startTicks = mainTicks - pauseTicks;
		pauseTicks = 0;
	}
}

void AdvancedTimer::TimerUpdate()
{
	mainTicks = SDL_GetTicks64();
}

int AdvancedTimer::GetTicks()
{
	// actual timer time
	int timeActual = 0;

	if (isStarted)
	{
		if (isPaused)
		{
			timeActual = pauseTicks;
		}
		else
		{
			timeActual = mainTicks - startTicks;

			/*
			std::cout << "GetTicks() mainTicks: " << mainTicks << std::endl;
			std::cout << "GetTicks() startTicks: " << startTicks << std::endl;
			*/
		}
	}

	//std::cout << "GetTicks() timeActual: " << timeActual << std::endl;
	return timeActual;
}

int AdvancedTimer::GetMainTicks()
{
	TimerUpdate();
	return mainTicks;
}

bool AdvancedTimer::GetIsStarted()
{
	return isStarted;
}

bool AdvancedTimer::GetIsPaused()
{
	return isPaused;
}
