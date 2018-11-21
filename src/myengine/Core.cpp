#include "Core.h"
#include "Entity.h"
#include "Environment.h"
#include "Resources.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"
#include "Shader.h"
#include <iostream>
#include <GL/glew.h>
#include <map>


namespace myengine
{

	Core::Core()
	{
		std::cout << "Created Core" << std::endl;
	}


	Core::~Core()
	{
		_entities.clear();

		std::cout << "Destroyed Core, Game Ended" << std::endl;
	}

	void Core::Init(std::weak_ptr<Core> self, int _width, int _height)
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

		_window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

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

		_self = self;

		std::shared_ptr<Entity> _camera = addEntity();
		std::shared_ptr<Camera> _cameraComponent = _camera->addComponent<Camera, float, float, float>(45.0f, 0.01f, 100.0f);
		setMainCamera(_cameraComponent);

		_input->setCorePtr(_self);

		HitboxShader = Shader::Create("../resources/fragmentshaders/collider.fs", "../resources/vertexshaders/collider.vs", { "in_position" }, _resources);
		SkyboxShader = Shader::Create("../resources/fragmentshaders/skybox.fs", "../resources/vertexshaders/skybox.vs", { "in_position" }, _resources);

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

			for (size_t i = 0; i < _entities.size(); i++)
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
						_input->QueueMouseMovementUpdate();
						break;
					}
					case SDL_MOUSEBUTTONDOWN:
					{
						_input->QueueMouseButtonUpdate();
					}
					case SDL_MOUSEBUTTONUP:
					{
						_input->QueueMouseButtonUpdate();
					}
					case SDL_JOYAXISMOTION:
					{
						_input->QueueControllerJoystickUpdate();
						break;
					}
					case SDL_JOYBUTTONDOWN:
					{
						_input->QueueControllerButtonUpdate();
						break;
					}
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

	std::shared_ptr<Entity> Core::addEntity(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();
		newEntity->init(_self, _position, _rotation, _scale);

		newEntity->setSelf(newEntity);

		_entities.push_back(newEntity);
		return newEntity;
	}

	std::shared_ptr<Entity> Core::addUiElement(glm::vec2 _position, float _rotation, glm::vec3 _scale)
	{
		std::shared_ptr<Entity> newUiEntity = std::make_shared<Entity>();
		newUiEntity->init(_self, glm::vec3(_position.x, _position.y, -5.0f), glm::vec3(0.0f, 0.0f, _rotation), _scale);

		newUiEntity->setSelf(newUiEntity);

		_UIElements.push_back(newUiEntity);

		return newUiEntity;
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

	std::shared_ptr<Shader> Core::getHitboxShader()
	{
		return HitboxShader;
	}

	std::shared_ptr<Shader> Core::getSkyboxShader()
	{
		return SkyboxShader;
	}

}