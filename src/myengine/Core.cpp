#include "Core.h"
#include "Entity.h"
#include "Environment.h"
#include "Resources.h"
#include "Camera.h"
#include "Input.h"
#include "Timer.h"
#include "Shader.h"
#include "Prefab.h"
#include "Pooler.h"
#include <iostream>
#include <GL/glew.h>
#include <map>
#include <exception>


namespace frontier
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

		device = alcOpenDevice(NULL);

		if (!device)
		{
			throw std::exception();
		}

		context = alcCreateContext(device, NULL);

		if (!context)
		{
			alcCloseDevice(device);
			throw std::exception();
		}

		if (!alcMakeContextCurrent(context))
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
			throw std::exception();
		}

		_self = self;

		std::shared_ptr<Entity> _camera = addEntity();
		std::shared_ptr<Camera> _cameraComponent = _camera->addComponent<Camera, float, float, float>(45.0f, 0.01f, 100.0f);
		setMainCamera(_cameraComponent);

		_input->setCorePtr(_self);

		HitboxShader = Shader::Create("../resources/fragmentshaders/collider.fs", "../resources/vertexshaders/collider.vs", { "in_position" }, _resources);
		SkyboxShader = Shader::Create("../resources/fragmentshaders/skybox.fs", "../resources/vertexshaders/skybox.vs", { "in_position" }, _resources);
		UntexturedUiImageShader = Shader::Create("../resources/fragmentshaders/untexui.fs", "../resources/vertexshaders/untexui.vs", { "in_position" }, _resources);
		TexturedUiImageShader = Shader::Create("../resources/fragmentshaders/texui.fs", "../resources/vertexshaders/texui.vs", { "in_position", "in_texCoord" }, _resources);

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
			

			for (size_t i = 0; i < _entitiesToActivate.size(); i++)
			{
				_entitiesToActivate[i]->setActive(true);
				_entitiesToActivate[i]->setActivating(false);
			}

			_entitiesToActivate.clear();

			for (size_t i = 0; i < _UIElements.size(); i++)
			{
				_UIElements[i]->tick();
			}

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
					/*case SDL_WINDOWEVENT:
					{
						if (_event.window.event == SDL_WINDOWEVENT_RESIZED || _event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
						{
							UpdateWindowSize(_event.window.data1, _event.window.data2);
						}
					}*/
				}
			}
				


			_environment->IncrementFrameCounter();

			if (_input->getKey(Input::ESC))
			{
				Stop();
			}
		}

		_input->FreeJoystick();
		alcMakeContextCurrent(NULL);
		alcDestroyContext(context);
		alcCloseDevice(device);
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

	std::shared_ptr<Entity> Core::addEntity(std::shared_ptr<Prefab> _prefab, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();

		newEntity->setSelf(newEntity);

		newEntity->init(_self, _prefab, _position, _rotation, _scale);

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

	std::shared_ptr<Prefab> Core::addPrefab()
	{
		std::shared_ptr<Prefab> newPrefab = std::make_shared<Prefab>();
		newPrefab->init(_self);

		newPrefab->setSelf(newPrefab);

		_prefabs.push_back(newPrefab);

		return newPrefab;
	}

	std::shared_ptr<Pooler> Core::addPooler(std::string _id, std::shared_ptr<Prefab> _prefab, int initialPoolSize)
	{
		std::shared_ptr<Pooler> rtn = std::make_shared<Pooler>();
		rtn->OnInit(_self, _id, _prefab, initialPoolSize);
		_poolers.push_back(rtn);
		return rtn;
	}

	std::shared_ptr<Pooler> Core::getPooler(std::string _poolID)
	{
		for (size_t i = 0; i < _poolers.size(); i++)
		{
			if (_poolers[i]->getID() == _poolID)
			{
				return _poolers[i];
			}
		}

		std::cout << "No pooler exists with the ID: " << _poolID << std::endl;
		throw std::exception();
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

	void Core::UpdateWindowSize(int _width, int _height)
	{
		_windowWidth = _width;
		_windowHeight = _height;
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

	std::shared_ptr<Shader> Core::getUntexturedUiImageShader()
	{
		return UntexturedUiImageShader;
	}

	std::shared_ptr<Shader> Core::getTexturedUiImageShader()
	{
		return TexturedUiImageShader;
	}

	void Core::AddToEntitiesToActivate(std::shared_ptr<Entity> _entityToActivate)
	{
		_entitiesToActivate.push_back(_entityToActivate);
	}

}