#ifndef CORE_H_
#define CORE_H_


#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "glm.hpp"

namespace myengine
{

	class Environment;
	class Entity;
	class Input;
	class Resources;
	class Camera;
	class Shader;

	class Core : public std::enable_shared_from_this<Core>
	{
	private:
		std::vector<std::shared_ptr<Entity>> _entities;
		std::vector<std::shared_ptr<Entity>> _UIElements;
		

		std::shared_ptr<Environment> _environment;
		std::shared_ptr<Input> _input;
		std::shared_ptr<Resources> _resources;
		std::weak_ptr<Core> _self;
		std::shared_ptr<Camera> _mainCamera;

		std::shared_ptr<Shader> HitboxShader;
		std::shared_ptr<Shader> SkyboxShader;

		SDL_Window *_window;
		SDL_Event _event;

		int _windowWidth, _windowHeight;
		bool _running;

		void GameLoop();

	public:
		Core();
		~Core();
		void Init(std::weak_ptr<Core> self, int _width = 800, int _height = 600);
		void Start();
		void Stop();
		std::shared_ptr<Entity> addEntity(glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));
		std::shared_ptr<Entity> addUiElement(glm::vec2 _position = glm::vec2(0.0f, 0.0f), float _rotation = 0.0f, glm::vec3 _scale = glm::vec3(0.0f, 0.0f, 0.0f));
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<Input> getInput();
		std::shared_ptr<Resources> getResources();
		void SetSelf(std::weak_ptr<Core> _selfPtr);
		int getWidth();
		int getHeight();
		std::shared_ptr<Camera> getMainCamera();
		void setMainCamera(std::shared_ptr<Camera> _mainCameraToSet);
		std::shared_ptr<Shader> getHitboxShader();
		std::shared_ptr<Shader> getSkyboxShader();


		template <typename T>
		std::vector<std::weak_ptr<Entity>> getEntitiesWithComponent()
		{
			std::vector<std::weak_ptr<Entity>> returnEntities;
			for (size_t i = 0; i < _entities.size(); i++)
			{
				if (_entities[i]->hasComponent<T>())
				{
					returnEntities.push_back(_entities[i]);
				}
			}

			return returnEntities;
		}


	};

}

#endif // !1