#include "Core.h"
#include "Entity.h"
#include <iostream>

Core::Core()
{
	std::cout << "Created Core" << std::endl;
}

Core::~Core()
{
	std::cout << "Destroyed Core, Game Ended" << std::endl;
}

std::shared_ptr<Core> Core::Init()
{
	//put other setup stuff here
	return std::shared_ptr<Core>(this);
}

void Core::Start()
{
	_running = true;
	GameLoop();
}

void Core::GameLoop()
{
	int _counter = 0;
	while (_running)
	{
		for (int i = 0; i < sizeof(_entities); i++)
		{
			_entities[i]->tick();
		}

		if (_counter > 3)
		{
			std::cout << "This is a break point before stopping" << std::endl;
			Stop();
		}
		else
		{
			_counter++;
		}
	}
}

void Core::Stop()
{
	_running = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();
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

