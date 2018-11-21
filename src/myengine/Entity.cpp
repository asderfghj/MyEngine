#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include <iostream>

namespace frontier
{

	Entity::Entity()
	{
		std::cout << "Entity Created" << std::endl;
	}

	Entity::~Entity()
	{
		_components.clear();
		std::cout << "Entity Destroyed" << std::endl;
	}

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
		std::shared_ptr<Transform> trans = addComponent<Transform>();
		trans->setSelf(trans);
	}

	void Entity::init(std::weak_ptr<Core> _corePtr, glm::vec3 _position)
	{
		_core = _corePtr;
		addComponent<Transform, glm::vec3>(_position);
	}

	void Entity::init(std::weak_ptr<Core> _corePtr, glm::vec3 _position, glm::vec3 _rotation)
	{
		_core = _corePtr;
		addComponent<Transform, glm::vec3, glm::vec3>(_position, _rotation);
	}

	void Entity::init(std::weak_ptr<Core> _corePtr, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		_core = _corePtr;
		addComponent<Transform, glm::vec3, glm::vec3, glm::vec3>(_position, _rotation, _scale);
	}

	void Entity::setSelf(std::weak_ptr<Entity> _selfPtr)
	{
		_self = _selfPtr;
	}

	std::shared_ptr<Core> Entity::getCore()
	{
		return _core.lock();
	}

}