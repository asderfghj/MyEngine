#include "Environment.h"
#include "Timer.h"
#include <iostream>

namespace frontier
{

	Environment::Environment()
	{
		std::cout << "Environment created" << std::endl;
		NOW = SDL_GetPerformanceCounter();
		LAST = 0;
		_deltatime = 0;
		_timer = std::make_shared<Timer>();
		_countedFrames = 0;
	}

	Environment::~Environment()
	{
		std::cout << "Environment destroyed" << std::endl;
	}

	float Environment::getDeltaTime()
	{
		return (float)_deltatime;
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

	std::shared_ptr<Timer> Environment::GetTimer()
	{
		return _timer;
	}

	void Environment::IncrementFrameCounter()
	{
		_countedFrames++;
	}

	int Environment::GetCountedFrames()
	{
		return _countedFrames;
	}

	float Environment::getFPS()
	{
		float avgFPS = _countedFrames / (GetTimer()->GetTicks() / 1000.0f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		return avgFPS;
	}

	float Environment::getRandomBetweenTwoValues(float _val1, float _val2)
	{
		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = _val2 - _val1;
		float r = random * diff;
		return _val1 + r;
	}

}