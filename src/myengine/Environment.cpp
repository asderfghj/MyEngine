#include "Environment.h"
#include <iostream>

Environment::Environment()
{
	std::cout << "Environment created" << std::endl;
}

Environment::~Environment()
{
	std::cout << "Environment destroyed" << std::endl;
}

float Environment::getDeltaTime()
{
	return _deltatime;
}

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