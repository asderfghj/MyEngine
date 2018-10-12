#include <memory>
#include <vector>
#include <SDL2/SDL.h>

class Environment;
class Entity;
class Input;

class Core : public std::enable_shared_from_this<Core>
{
private:
	std::vector<std::shared_ptr<Entity>> _entities;

	std::shared_ptr<Environment> _environment;
	std::shared_ptr<Input> _input;
	std::weak_ptr<Core> _self;

	SDL_Window *_window;

	int _windowWidth, _windowHeight;
	bool _running;

	void GameLoop();

public:
	Core();
	~Core();
	void Init();
	void Init(int _width, int _height);
	void Start();
	void Stop();
	std::shared_ptr<Entity> addEntity();
	std::shared_ptr<Environment> getEnvironment();
	std::shared_ptr<Input> getInput();
	void SetSelf(std::weak_ptr<Core> _selfPtr);
};