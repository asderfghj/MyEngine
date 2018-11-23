#ifndef CORE_H_
#define CORE_H_


#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "glm.hpp"
#include <string>
#include <AL/al.h>
#include <AL/alc.h>

namespace frontier
{

	class Environment;
	class Entity;
	class Input;
	class Resources;
	class Camera;
	class Shader;
	class Prefab;
	class Pooler;

	class Core : public std::enable_shared_from_this<Core>
	{
	private:
		std::vector<std::shared_ptr<Entity>> _entities;
		std::vector<std::shared_ptr<Entity>> _UIElements;
		std::vector<std::shared_ptr<Prefab>> _prefabs;
		std::vector<std::shared_ptr<Pooler>> _poolers;
		std::vector<std::shared_ptr<Entity>> _entitiesToActivate;

		std::shared_ptr<Environment> _environment;
		std::shared_ptr<Input> _input;
		std::shared_ptr<Resources> _resources;
		std::weak_ptr<Core> _self;
		std::shared_ptr<Camera> _mainCamera;

		//default Shaders
		std::shared_ptr<Shader> HitboxShader;
		std::shared_ptr<Shader> SkyboxShader;
		std::shared_ptr<Shader> UntexturedUiImageShader;
		std::shared_ptr<Shader> TexturedUiImageShader;

		SDL_Window *_window;
		SDL_Event _event;
		ALCdevice* device;
		ALCcontext* context;

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
		std::shared_ptr<Entity> addEntity(std::shared_ptr<Prefab> _prefab, glm::vec3 _position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _rotation = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));
		std::shared_ptr<Entity> addUiElement(glm::vec2 _position = glm::vec2(0.0f, 0.0f), float _rotation = 0.0f, glm::vec3 _scale = glm::vec3(1.0f, 1.0f, 1.0f));
		std::shared_ptr<Prefab> addPrefab();
		std::shared_ptr<Pooler> addPooler(std::string _id, std::shared_ptr<Prefab> _prefab, int initialPoolSize);
		std::shared_ptr<Pooler> getPooler(std::string _poolID);
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<Input> getInput();
		std::shared_ptr<Resources> getResources();
		void SetSelf(std::weak_ptr<Core> _selfPtr);
		int getWidth();
		int getHeight();
		void UpdateWindowSize(int _width, int _height);
		std::shared_ptr<Camera> getMainCamera();
		void setMainCamera(std::shared_ptr<Camera> _mainCameraToSet);

		//default shader getters
		std::shared_ptr<Shader> getHitboxShader();
		std::shared_ptr<Shader> getSkyboxShader();
		std::shared_ptr<Shader> getUntexturedUiImageShader();
		std::shared_ptr<Shader> getTexturedUiImageShader();

		void AddToEntitiesToActivate(std::shared_ptr<Entity> _entityToActivate);


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