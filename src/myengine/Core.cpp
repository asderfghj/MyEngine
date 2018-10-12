#include "Core.h"
#include "Entity.h"
#include "Environment.h"
#include <iostream>
#include <GL/glew.h>

Core::Core()
{
	std::cout << "Created Core" << std::endl;
	this->Init();
}

Core::~Core()
{
	std::cout << "Destroyed Core, Game Ended" << std::endl;
}

void Core::Init()
{
	//put other setup stuff here
	_environment = std::make_shared<Environment>();
	_window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(_window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}
}

void Core::Start()
{
	_running = true;
	GameLoop();
}

void Core::GameLoop()
{
	while (_running)
	{
		SDL_Event _event = { 0 };

		glClear(GL_COLOR_BUFFER_BIT);

		for (int i = 0; i < _entities.size(); i++)
		{
			_entities[i]->tick();
		}

		SDL_GL_SwapWindow(_window);

		while (SDL_PollEvent(&_event))
		{
			if (_event.type == SDL_QUIT)
			{
				Stop();
			}
		}

	}

	SDL_DestroyWindow(_window);
	SDL_Quit();
}

void Core::Stop()
{
	_running = false;
}

std::shared_ptr<Entity> Core::addEntity()
{
	std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();
	newEntity->init(_self);

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

void Core::SetSelf(std::weak_ptr<Core> _selfPtr)
{
	_self = _selfPtr;
}

