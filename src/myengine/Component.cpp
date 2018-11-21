#include "Component.h"
#include "Entity.h"
#include "Core.h"
#include <iostream>

namespace myengine
{

	Component::Component()
	{
		std::cout << "Component Created" << std::endl;
	}

	Component::~Component()
	{
		std::cout << "Component Destroyed" << std::endl;
	}

	std::shared_ptr<Entity> Component::getEntity()
	{
		return _entity.lock();
	}

	std::shared_ptr<Core> Component::getCore()
	{
		if (!_entity.expired())
		{
			return _entity.lock()->getCore();
		}
		else
		{
			throw std::exception();
		}
	}

	std::shared_ptr<Input> Component::getInput()
	{
		return getCore()->getInput();
	}

	std::shared_ptr<Environment> Component::getEnvironment()
	{
		return getCore()->getEnvironment();
	}

	void Component::OnInit(std::weak_ptr<Entity> _parent)
	{
		_entity = _parent;
	}

	void Component::OnBegin()
	{

	}

	void Component::OnTick()
	{
	}

	void Component::OnDisplay()
	{

	}

}