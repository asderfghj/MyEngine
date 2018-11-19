#include <SDL2/SDL.h>
#include <memory>

namespace myengine
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

	};
}