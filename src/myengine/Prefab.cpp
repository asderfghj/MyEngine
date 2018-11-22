#include "Prefab.h"

namespace frontier
{
	void Prefab::init(std::weak_ptr<Core> _coreptr)
	{
		_core = _coreptr;
	}

	std::vector<std::shared_ptr<Component>> Prefab::getComponents()
	{
		return _components;
	}

}