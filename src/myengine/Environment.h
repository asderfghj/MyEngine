#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <SDL2/SDL.h>
#include <memory>

namespace frontier
{

	class Timer;

	class Environment
	{
	private:
		double _deltatime;
		Uint64 LAST, NOW;
		std::shared_ptr<Timer> _timer;
		int _countedFrames;
	public:
		Environment();
		~Environment();
		float getDeltaTime();
		void tick();
		std::shared_ptr<Timer> GetTimer();
		void IncrementFrameCounter();
		int GetCountedFrames();
		float getFPS();
		float getRandomBetweenTwoValues(float _val1, float _val2);
		Uint32 getTime();
	};
}

#endif