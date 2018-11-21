#include <SDL2/SDL.h>


namespace frontier 
{
	class Timer
	{
	public:
		Timer();

		void Start();
		void Stop();
		void Pause();
		void Unpause();

		Uint32 GetTicks();

		bool IsStarted();
		bool IsPaused();

	private:
		Uint32 _startTicks;
		Uint32 _pausedTicks;
		bool _paused;
		bool _started;
	};
}