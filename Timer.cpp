 #include "Timer.h"

Timer::Timer(){
	
}
bool Timer::init(){
	Uint32 wasInit = SDL_WasInit(SDL_INIT_TIMER);
	if(wasInit & SDL_INIT_TIMER){
		running = false;
		paused = false;
		startingTime = 0;
		pausedTime = 0;
	}
	else{
		printf("Timer failed to Initialize\n");
		return false;
	}
	
	return true;
}
void Timer::start(){
	startingTime = SDL_GetTicks();
	running = true;
	paused = false;
}
void Timer::stop(){
	running = false;
	startingTime = 0;
	pausedTime = 0;
}
void Timer::pause(){
	if(paused) return;
	paused = true;
	pausedTime = SDL_GetTicks() - startingTime;
}
void Timer::unpause(){
	if(!paused) return;
	paused = false;
	startingTime = SDL_GetTicks() - pausedTime;
}
bool Timer::isRunning(){
	return running;
}
bool Timer::isPaused(){
	return paused;
}
Uint32 Timer::getTime(){
	if(paused) return pausedTime;
	else return SDL_GetTicks() - startingTime;
}

