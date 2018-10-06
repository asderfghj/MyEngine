#include "Entity.h"
#include "Component.h"

void Entity::tick()
{
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

