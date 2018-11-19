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

	class Core : public std::enable_shared_from_this<Core>
	{
	private:
		std::vector<std::shared_ptr<Entity>> _entities;
		

		std::shared_ptr<Environment> _environment;
		std::shared_ptr<Input> _input;
		std::shared_ptr<Resources> _resources;
		std::weak_ptr<Core> _self;
		std::shared_ptr<Camera> _mainCamera;

		SDL_Window *_window;
		SDL_Event _event;

		int _windowWidth, _windowHeight;
		bool _running;

		void GameLoop();

	public:
		Core();
		~Core();
		void Init();
		void Init(int _width, int _height);
		void Start();
		void Stop();
		std::shared_ptr<Entity> addEntity();
		std::shared_ptr<Entity> addEntity(glm::vec3 _position);
		std::shared_ptr<Entity> addEntity(glm::vec3 _position, glm::vec3 _rotation);
		std::shared_ptr<Entity> addEntity(glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
		std::shared_ptr<Environment> getEnvironment();
		std::shared_ptr<Input> getInput();
		std::shared_ptr<Resources> getResources();
		void SetSelf(std::weak_ptr<Core> _selfPtr);
		int getWidth();
		int getHeight();
		std::shared_ptr<Camera> getMainCamera();
		void setMainCamera(std::shared_ptr<Camera> _mainCameraToSet);
		SDL_Event* getEvent();
	};

}

#endif // !1