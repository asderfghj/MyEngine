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
	newEntity->init(std::shared_ptr<Core>(this));
	_entities.push_back(newEntity);
	return newEntity;
}


std::shared_ptr<Environment> Core::getEnvironment()
{
	return _environment;
}

std::shared_ptr<Input> Core::getInput()
{
	return _input;
}

