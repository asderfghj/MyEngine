#include "Core.h"
#include "Entity.h"
#include "Environment.h"
#include "Resources.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"
#include <iostream>
#include <GL/glew.h>
#include <map>

namespace myengine
{

	Core::Core()
	{
		std::cout << "Created Core" << std::endl;
		this->Init();
	}

	Core::Core(int width, int height)
	{
		std::cout << "Created Core" << std::endl;
		this->Init(width, height);
	}

	Core::~Core()
	{
		_entities.clear();

		std::cout << "Destroyed Core, Game Ended" << std::endl;
	}

	void Core::Init()
	{
		//put other setup stuff here
		if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
		{
			std::cout << "Joystick functionality could not be initialised" << std::endl;
			throw std::exception();
		}
		_environment = std::make_shared<Environment>();
		_resources = std::make_shared<Resources>();
		_input = std::make_shared<Input>();

		_window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL /*| SDL_WINDOW_INPUT_GRABBED*/);

		_windowHeight = 480;
		_windowWidth = 640;

		if (!SDL_GL_CreateContext(_window))
		{
			throw std::exception();
		}

		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		glEnable(GL_DEPTH_TEST);
		//SDL_ShowCursor(SDL_DISABLE);
		//SDL_WarpMouseInWindow(_window, 320, 240);
		//SDL_CaptureMouse(SDL_TRUE);
		//SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	void Core::Init(int _width, int _height)
	{
		//put other setup stuff here
		if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
		{
			std::cout << "Joystick functionality could not be initialised" << std::endl;
			throw std::exception();
		}
		_environment = std::make_shared<Environment>();
		_resources = std::make_shared<Resources>();
		_input = std::make_shared<Input>();

		_window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL /*| SDL_WINDOW_INPUT_GRABBED*/);

		_windowHeight = _height;
		_windowWidth = _width;

		if (!SDL_GL_CreateContext(_window))
		{
			throw std::exception();
		}

		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		glEnable(GL_DEPTH_TEST);
		//SDL_ShowCursor(SDL_DISABLE);
		//SDL_WarpMouseInWindow(_window, 320, 240);
		//SDL_CaptureMouse(SDL_TRUE);
		//SDL_SetRelativeMouseMode(SDL_TRUE);
	}

	void Core::Start()
	{
		_running = true;
		GameLoop();
	}

	void Core::GameLoop()
	{
		_environment->GetTimer()->Start();

		while (_running)
		{
			_event = { 0 };

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (int i = 0; i < _entities.size(); i++)
			{
				_entities[i]->tick();
			}
			_environment->tick();
			_input->Tick();
			SDL_GL_SwapWindow(_window);
			std::map<int, bool> keyboard;
			glm::vec2 LeftStick, RightStick;
			while (SDL_PollEvent(&_event))
			{
				
				switch (_event.type)
				{
					case SDL_KEYDOWN:
					{
						_input->QueueKeyboardUpdate();
						break;
					}
					case SDL_KEYUP:
					{
						_input->QueueKeyboardUpdate();
						break;
					}
					case SDL_QUIT:
					{
						Stop();
						break;
					}
					case SDL_MOUSEMOTION:
					{
						_input->UpdateMouse();
						break;
					}
					case SDL_JOYAXISMOTION:
					{
						_input->QueueControllerJoystickUpdate();
						break;
					}
					case SDL_JOYBUTTONDOWN:
					case SDL_JOYBUTTONUP:
					{
						_input->QueueControllerButtonUpdate();
						break;
					}
					case SDL_JOYHATMOTION:
					{
						_input->QueueControllerDpadUpdate();
						break;
					}
				}
			}
				


			_environment->IncrementFrameCounter();

			if (_input->getKey(Input::ESC))
			{
				Stop();
			}
		}

		_input->FreeJoystick();
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

	std::shared_ptr<Entity> Core::addEntity(glm::vec3 _position)
	{
		std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();
		newEntity->init(_self, _position);

		_entities.push_back(newEntity);
		return newEntity;
	}

	std::shared_ptr<Entity> Core::addEntity(glm::vec3 _position, glm::vec3 _rotation)
	{
		std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();
		newEntity->init(_self, _position, _rotation);

		_entities.push_back(newEntity);
		return newEntity;
	}
	std::shared_ptr<Entity> Core::addEntity(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();
		newEntity->init(_self, _position, _rotation, _scale);

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

	std::shared_ptr<Resources> Core::getResources()
	{
		return _resources;
	}

	void Core::SetSelf(std::weak_ptr<Core> _selfPtr)
	{
		_self = _selfPtr;
		std::shared_ptr<Entity> _camera = addEntity();
		_camera->setSelf(_camera);
		std::shared_ptr<Camera> _cameraComponent = _camera->addComponent<Camera, float, float, float>(45.0f, 0.01f, 100.0f);
		setMainCamera(_cameraComponent);
		_cameraComponent->setControllable(true);
		_input->setCorePtr(_self);
	}

	int Core::getWidth()
	{
		return _windowWidth;
	}

	int Core::getHeight()
	{
		return _windowHeight;
	}

	std::shared_ptr<Camera> Core::getMainCamera()
	{
		return _mainCamera;;
	}

	void Core::setMainCamera(std::shared_ptr<Camera> _mainCameraToSet)
	{
		_mainCamera = _mainCameraToSet;
	}

	SDL_Event* Core::getEvent()
	{
		return &_event;
	}

}