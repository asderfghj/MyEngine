#include <SDL2/SDL.h>

class Environment
{
public:
	Environment();
	~Environment();
	float getDeltaTime();
	void tick();

private:
	double _deltatime;
	Uint64 LAST, NOW;

};
