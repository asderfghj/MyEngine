#ifndef COMPONENT_H_
#define COMPONENT_H_


#include <memory>

class Entity;
class Core;
class Input;
class Environment;

class Component
{
private:
	std::weak_ptr<Entity> _entity;

protected:
	std::shared_ptr<Entity> getEntity();
	std::shared_ptr<Core> getCore();
	std::shared_ptr<Input> getInput();
	std::shared_ptr<Environment> getEnvironment();

public:
	Component();
	~Component();
	virtual void OnInit(std::weak_ptr<Entity> _parent);
	virtual void OnBegin();
	virtual void OnTick();
	virtual void OnDisplay();
};

#endif