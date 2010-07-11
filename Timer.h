#ifndef INCLUDED_TIMER_H
#define INCLUDED_TIMER_H

#include "SDL/SDL.h"
/*
Simple class to keep track of time
Do not call start until after SDL_Init has been called
*/
class Timer{
	public:
		Timer();
		bool init();
		void start();
		void stop();
		void pause();
		void unpause();
		bool isRunning();
		bool isPaused();
		Uint32 getTime();
	private:
		unsigned int startingTime, pausedTime;
		bool paused, running;
};

#endif
