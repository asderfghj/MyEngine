#include <vector>
#include <memory>

class Component;
class Core;

class Entity
{
private:
	std::vector<std::shared_ptr<Component>> _components;
	std::weak_ptr<Core> _core;
	void tick();
	void display();

public:
	std::shared_ptr<Core> getCore();

	template <typename T>
	std::shared_ptr<T> addComponent()
	{
		std::shared_ptr <T> t(new T());
		t->init();
		_components.push_back(t);
	}

	template <typename T, typename A>
	std::shared_ptr<T> addComponent(A _a)
	{
		std::shared_ptr <T> t(new T(_a));
		t->init();
		_components.push_back(t);
	}

	template <typename T, typename A, typename B>
	std::shared_ptr<T> addComponent(A _a, B _b)
	{
		std::shared_ptr <T> t(new T(_a, _b));
		t->init();
		_components.push_back(t);
	}

	template <typename T, typename A, typename B, typename C>
	std::shared_ptr<T> addComponent(A _a, B _b, C _c)
	{
		std::shared_ptr <T> t(new T());
		t->init();
		_components.push_back(t);
	}

	template <typename T, typename A, typename B, typename C, typename D>
	std::shared_ptr<T> addComponent(A _a, B _b, C _c, D _d)
	{
		std::shared_ptr <T> t(new T());
		t->init();
		_components.push_back(t);
	}



};
