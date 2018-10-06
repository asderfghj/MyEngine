#include "Component.h"
#include "Entity.h"
#include "Core.h"

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