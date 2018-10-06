#include "Environment.h"

void Environment::tick()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	_deltatime = (double)((NOW - LAST) * 1000 / (double)SDL_GetPerformanceFrequency());
	if (_deltatime > 0.15)
	{
		_deltatime = 0.15;
	}
	//primarily for deltatime but if other stuff needs updating add it here as this will be called every frame from core.
}