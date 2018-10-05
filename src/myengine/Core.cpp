#include "Core.h"
#include "Entity.h"

std::shared_ptr<Core> Core::Init()
{
	
	//put other setup stuff here
	return std::shared_ptr<Core>(this);
}

void Core::Start()
{
	_running = true;
}

void Core::Stop()
{
	_running = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr <Entity> newEntity(new Entity());
	_entities.push_back(newEntity);
	return newEntity;
}

