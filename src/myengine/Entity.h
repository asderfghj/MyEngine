#include <vector>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <iostream>
#include <assert.h>
#include "Component.h"
#include "glm.hpp"

namespace myengine
{

	class Core;

	class Entity : std::enable_shared_from_this<Entity>
	{
	private:
		std::vector<std::shared_ptr<Component>> _components;
		std::weak_ptr<Core> _core;
		std::weak_ptr<Entity> _self;
		void display();


	public:

		Entity();
		~Entity();
		void init(std::weak_ptr<Core> _corePtr);
		void init(std::weak_ptr<Core> _corePtr, glm::vec3 _position);
		void init(std::weak_ptr<Core> _corePtr, glm::vec3 _position, glm::vec3 _rotation);
		void init(std::weak_ptr<Core> _corePtr, glm::vec3 _position, glm::vec3 _rotation, glm::vec3 _scale);
		std::shared_ptr<Core> getCore();
		void tick();
		void setSelf(std::weak_ptr<Entity> _selfPtr);

		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();

			_components.push_back(t);

			t->OnInit(_self);
			return t;
		}

		template <typename T, typename A>
		std::shared_ptr<T> addComponent(A _a)
		{

			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(_self, _a);
			_components.push_back(t);
			return t;
		}

		template <typename T, typename A, typename B>
		std::shared_ptr<T> addComponent(A _a, B _b)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(_self, _a, _b);
			_components.push_back(t);
			return t;
		}

		template <typename T, typename A, typename B, typename C>
		std::shared_ptr<T> addComponent(A _a, B _b, C _c)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(_self, _a, _b, _c);
			_components.push_back(t);
			return t;
		}

		template <typename T, typename A, typename B, typename C, typename D>
		std::shared_ptr<T> addComponent(A _a, B _b, C _c, D _d)
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			std::shared_ptr <T> t = std::make_shared<T>();
			t->OnInit(_self, _a, _b, _c, _d);
			_components.push_back(t);
			return t;
		}

		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (size_t i = 0; i < _components.size(); i++)
			{
				std::shared_ptr<T> returnPtr = std::dynamic_pointer_cast<T>(_components.at(i));

				if (returnPtr)
				{
					return returnPtr;
				}
				std::cout << "this is iterating" << std::endl;
			}
			throw std::exception();


		}

	};

}