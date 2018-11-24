#ifndef PREFAB_H_
#define PREFAB_H_

#include <vector>
#include <memory>
#include "Transform.h"
#include "Component.h"
#include "Entity.h"

namespace frontier
{
	class Core;

	class Prefab : public Entity
	{
	private:
		std::vector<std::shared_ptr<Component>> _components;


	public:
		void init(std::weak_ptr<Core> _coreptr) override;
		std::vector<std::shared_ptr<Component>> getComponents();

		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			static_assert(std::is_base_of<Component, T>(), "Datatype must be derived of component");
			//static_assert(std::is_base_of<Transform, T>(), "Prefabs cannot contain a transform, Transforms are applied in Entities");
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
			}
			throw std::exception();


		}

	};
}

#endif // !PREFAB_H_