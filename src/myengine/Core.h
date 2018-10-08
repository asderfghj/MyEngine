#include <memory>
#include <vector>

class Environment;
class Entity;
class Input;

class Core
{
private:
	std::shared_ptr<Environment> _environment;
	std::vector<std::shared_ptr<Entity>> _entities;
	std::shared_ptr<Input> _input;
	bool _running;
	void GameLoop();

public:
	Core();
	~Core();
	std::shared_ptr<Core> Init();
	void Start();
	void Stop();
	std::shared_ptr<Entity> addEntity();
	std::shared_ptr<Environment> getEnvironment();
	std::shared_ptr<Input> getInput();
};