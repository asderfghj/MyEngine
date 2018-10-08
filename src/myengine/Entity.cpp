#include "Entity.h"
#include "Component.h"
#include <iostream>

Entity::Entity()
{
	std::cout << "Entity Created" << std::endl;
}

Entity::~Entity()
{
	std::cout << "Entity Destroyed" << std::endl;
}

void Entity::tick()
{
	std::cout << "Entity Ticking" << std::endl;
	for each (std::shared_ptr<Component> _c in _components)
	{
		_c->OnTick();
	}
}

void Entity::display()
{
	//I have absolutley no clue...
}

void Entity::init(std::weak_ptr<Core> _corePtr)
{
	//any other stuff here
	_core = _corePtr;
}

std::shared_ptr<Core> Entity::getCore()
{
	return _core.lock();
}

