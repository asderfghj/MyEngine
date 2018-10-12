#include <SDL2/SDL.h>

class Environment
{
private:
	double _deltatime;
	Uint64 LAST, NOW;

public:
	Environment();
	~Environment();
	float getDeltaTime();
	void tick();

};
