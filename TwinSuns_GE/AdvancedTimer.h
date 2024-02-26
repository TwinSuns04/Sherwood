// Manages a timer that can start, stop, pause, unpause

#pragma once

#include "SDL.h"

class AdvancedTimer
{

public:

	// Constructor
	AdvancedTimer();

	// Functions, handle timer functionality
	void TimerStart();
	void TimerStop();
	void TimerPause();
	void TimerUnpause();
	void TimerUpdate();
	int GetTicks();
	int GetMainTicks();
	bool GetIsStarted();
	bool GetIsPaused();

private:

	// variables
	bool isStarted;
	bool isPaused;
	int startTicks;
	int pauseTicks;
	int mainTicks;

};
