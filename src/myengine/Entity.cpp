#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "Prefab.h"
#include "MeshRenderer.h"
#include "Collider.h"
#include "AsteroidBehavior.h"
#include "ProjectileBehavior.h"
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
		if (_active)
		{
			for each (std::shared_ptr<Component> _c in _components)
			{
				_c->OnTick();
			}
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

	void Entity::init(std::weak_ptr<Core> _corePtr, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		_core = _corePtr;
		addComponent<Transform, glm::vec3, glm::vec3, glm::vec3>(_position, _rotation, _scale);
	}

	void Entity::init(std::weak_ptr<Core> _corePtr, std::shared_ptr<Prefab> _prefab, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		_core = _corePtr;
		addComponent<Transform, glm::vec3, glm::vec3, glm::vec3>(_position, _rotation, _scale);
		for (int i = 0; i < _prefab->getComponents().size(); i++)
		{

			if (typeid(*_prefab->getComponents()[i]).name() == typeid(MeshRenderer).name())
			{
				addCopyOfComponent<MeshRenderer>(_prefab->getComponent<MeshRenderer>());
			}

			else if (typeid(*_prefab->getComponents()[i]).name() == typeid(Collider).name())
			{
				addCopyOfComponent<Collider>(_prefab->getComponent<Collider>());
			}

			else if (typeid(*_prefab->getComponents()[i]).name() == typeid(AsteroidBehavior).name())
			{
				addComponent<AsteroidBehavior>();
			}

			else if (typeid(*_prefab->getComponents()[i]).name() == typeid(ProjectileBehavior).name())
			{
				addCopyOfComponent<ProjectileBehavior>(_prefab->getComponent<ProjectileBehavior>());
			}

			else
			{
				std::cout << "WARNING: Component type: " << typeid(*_prefab->getComponents()[i]).name() << " is not copyable, it will not be added to this enitity" << std::endl;
			}
		}
	}

	void Entity::setSelf(std::weak_ptr<Entity> _selfPtr)
	{
		_self = _selfPtr;
	}

	void Entity::setActive(bool active)
	{
		if (active && !_active)
		{
			_active = active;
			for (int i = 0; i < _components.size(); i++)
			{
				_components[i]->OnActivate();
			}
		}
		else
		{
			_active = active;
		}
	}

	void Entity::setActivating(bool activating)
	{
		_activating = activating;
	}

	bool Entity::isActive()
	{
		return _active;
	}

	bool Entity::isActivating()
	{
		return _activating;
	}

	std::shared_ptr<Core> Entity::getCore()
	{
		return _core.lock();
	}

}