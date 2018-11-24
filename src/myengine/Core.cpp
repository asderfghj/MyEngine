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
	void Core::GameLoop()
	{
		m_environment->GetTimer()->Start();

		while (m_running)
		{
			m_event = { 0 };

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//activates any entities that have been flagged for activation.
			for (size_t i = 0; i < m_entitiesToActivate.size(); i++)
			{
				m_entitiesToActivate[i]->SetActive(true);
				m_entitiesToActivate[i]->SetActivating(false);
			}

			m_entitiesToActivate.clear();

			//ticks through all ui and regular entities and other classes
			for (size_t i = 0; i < m_uiElements.size(); i++)
			{
				m_uiElements[i]->Tick();
			}

			for (size_t i = 0; i < m_entities.size(); i++)
			{
				m_entities[i]->Tick();
			}

			m_environment->Tick();
			m_input->Tick();

			SDL_GL_SwapWindow(m_window);

			//input handling
			glm::vec2 leftStick, rightStick;
			while (SDL_PollEvent(&m_event))
			{

				switch (m_event.type)
				{
				case SDL_KEYDOWN:
				{
					m_input->QueueKeyboardUpdate();
					break;
				}
				case SDL_KEYUP:
				{
					m_input->QueueKeyboardUpdate();
					break;
				}
				case SDL_QUIT:
				{
					Stop();
					break;
				}
				case SDL_MOUSEMOTION:
				{
					m_input->QueueMouseMovementUpdate();
					break;
				}
				case SDL_MOUSEBUTTONDOWN:
				{
					m_input->QueueMouseButtonUpdate();
				}
				case SDL_MOUSEBUTTONUP:
				{
					m_input->QueueMouseButtonUpdate();
				}
				case SDL_JOYAXISMOTION:
				{
					m_input->QueueControllerJoystickUpdate();
					break;
				}
				case SDL_JOYBUTTONDOWN:
				{
					m_input->QueueControllerButtonUpdate();
					break;
				}
				case SDL_JOYBUTTONUP:
				{
					m_input->QueueControllerButtonUpdate();
					break;
				}
				case SDL_JOYHATMOTION:
				{
					m_input->QueueControllerDpadUpdate();
					break;
				}
				}
			}

			m_environment->IncrementFrameCounter();

			if (m_input->GetKey(Input::ESC))
			{
				Stop();
			}
		}
		//cleanup
		m_input->FreeJoystick();
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_context);
		alcCloseDevice(m_device);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	Core::~Core()
	{
		m_entities.clear();
		m_uiElements.clear();
		m_prefabs.clear();
		m_poolers.clear();
		m_entitiesToActivate.clear();
	}

	void Core::Init(std::weak_ptr<Core> _self, int _width, int _height)
	{
		//SDL joystick setup
		if (SDL_Init(SDL_INIT_JOYSTICK) < 0)
		{
			std::cout << "Joystick functionality could not be initialised" << std::endl;
			throw std::exception();
		}

		//important class initialisation
		m_environment = std::make_shared<Environment>();
		m_resources = std::make_shared<Resources>();
		m_input = std::make_shared<Input>();
		m_input->SetCorePtr(_self);

		//creating SDL window
		m_window = SDL_CreateWindow("window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

		m_windowHeight = _height;
		m_windowWidth = _width;

		if (!SDL_GL_CreateContext(m_window))
		{
			throw std::exception();
		}

		//OpenGL intialisation
		if (glewInit() != GLEW_OK)
		{
			throw std::exception();
		}

		glEnable(GL_DEPTH_TEST);

		//OpenAL initialisation
		m_device = alcOpenDevice(NULL);

		if (!m_device)
		{
			throw std::exception();
		}

		m_context = alcCreateContext(m_device, NULL);

		if (!m_context)
		{
			alcCloseDevice(m_device);
			throw std::exception();
		}

		if (!alcMakeContextCurrent(m_context))
		{
			alcDestroyContext(m_context);
			alcCloseDevice(m_device);
			throw std::exception();
		}

		//self pointer
		m_self = _self;

		//main camera initialisation
		std::shared_ptr<Entity> _camera = AddEntity();
		std::shared_ptr<Camera> _cameraComponent = _camera->AddComponent<Camera, float, float, float>(45.0f, 0.01f, 100.0f);
		SetMainCamera(_cameraComponent);

		//default shader initialisation
		m_hitboxShader = Shader::Create("../resources/fragmentshaders/collider.fs", "../resources/vertexshaders/collider.vs", { "in_position" }, m_resources);
		m_skyboxShader = Shader::Create("../resources/fragmentshaders/skybox.fs", "../resources/vertexshaders/skybox.vs", { "in_position" }, m_resources);
		m_untexturedUIImageShader = Shader::Create("../resources/fragmentshaders/untexui.fs", "../resources/vertexshaders/untexui.vs", { "in_position" }, m_resources);
		m_texturedUIImageShader = Shader::Create("../resources/fragmentshaders/texui.fs", "../resources/vertexshaders/texui.vs", { "in_position", "in_texCoord" }, m_resources);

	}

	void Core::Start()
	{
		m_running = true;
		GameLoop();
	}

	void Core::Stop()
	{
		m_running = false;
	}

	std::shared_ptr<Entity> Core::AddEntity(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();
		newEntity->Init(m_self, _position, _rotation, _scale);

		newEntity->SetSelf(newEntity);

		m_entities.push_back(newEntity);
		return newEntity;
	}

	std::shared_ptr<Entity> Core::AddEntity(std::shared_ptr<Prefab> _prefab, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale)
	{
		std::shared_ptr <Entity> newEntity = std::make_shared<Entity>();

		newEntity->SetSelf(newEntity);

		newEntity->Init(m_self, _prefab, _position, _rotation, _scale);

		m_entities.push_back(newEntity);
		return newEntity;
	}

	std::shared_ptr<Entity> Core::AddUIElement(glm::vec2 _position, float _rotation, glm::vec3 _scale)
	{
		std::shared_ptr<Entity> newUiEntity = std::make_shared<Entity>();
		newUiEntity->Init(m_self, glm::vec3(_position.x, _position.y, -5.0f), glm::vec3(0.0f, 0.0f, _rotation), _scale);

		newUiEntity->SetSelf(newUiEntity);

		m_uiElements.push_back(newUiEntity);

		return newUiEntity;
	}

	std::shared_ptr<Prefab> Core::AddPrefab()
	{
		std::shared_ptr<Prefab> newPrefab = std::make_shared<Prefab>();
		newPrefab->Init(m_self);

		newPrefab->SetSelf(newPrefab);

		m_prefabs.push_back(newPrefab);

		return newPrefab;
	}

	std::shared_ptr<Pooler> Core::AddPooler(std::string _id, std::shared_ptr<Prefab> _prefab, int _initialPoolSize)
	{
		std::shared_ptr<Pooler> rtn = std::make_shared<Pooler>();
		rtn->OnInit(m_self, _id, _prefab, _initialPoolSize);
		m_poolers.push_back(rtn);
		return rtn;
	}

	std::shared_ptr<Pooler> Core::GetPooler(std::string _poolID)
	{
		for (size_t i = 0; i < m_poolers.size(); i++)
		{
			if (m_poolers[i]->GetID() == _poolID)
			{
				return m_poolers[i];
			}
		}

		std::cout << "No pooler exists with the ID: " << _poolID << std::endl;
		throw std::exception();
	}

	std::shared_ptr<Environment> Core::GetEnvironment()
	{
		return m_environment;
	}

	std::shared_ptr<Input> Core::GetInput()
	{
		return m_input;
	}

	std::shared_ptr<Resources> Core::GetResources()
	{
		return m_resources;
	}

	void Core::SetSelf(std::weak_ptr<Core> _selfPtr)
	{
		m_self = _selfPtr;

	}

	int Core::GetWidth()
	{
		return m_windowWidth;
	}

	int Core::GetHeight()
	{
		return m_windowHeight;
	}

	std::shared_ptr<Camera> Core::GetMainCamera()
	{
		return m_mainCamera;;
	}

	void Core::SetMainCamera(std::shared_ptr<Camera> _mainCameraToSet)
	{
		m_mainCamera = _mainCameraToSet;
	}

	void Core::DeactivateAllInstancesInPools()
	{
		for (size_t i = 0; i < m_poolers.size(); i++)
		{
			m_poolers[i]->DeactivateAllInstances();
		}
	}

	std::shared_ptr<Shader> Core::getHitboxShader()
	{
		return m_hitboxShader;
	}

	std::shared_ptr<Shader> Core::getSkyboxShader()
	{
		return m_skyboxShader;
	}

	std::shared_ptr<Shader> Core::getUntexturedUiImageShader()
	{
		return m_untexturedUIImageShader;
	}

	std::shared_ptr<Shader> Core::getTexturedUiImageShader()
	{
		return m_texturedUIImageShader;
	}

	void Core::AddToEntitiesToActivate(std::shared_ptr<Entity> _entityToActivate)
	{
		m_entitiesToActivate.push_back(_entityToActivate);
	}

}