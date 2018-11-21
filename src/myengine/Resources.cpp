#include "Resources.h"
#include <iostream>

namespace frontier
{
	Resources::Resources()
	{
		std::cout << "Resources Created" << std::endl;
	}

	Resources::~Resources()
	{
		std::cout << "Resources Destroyed" << std::endl;
	}

	void Resources::AddCreatedResource(std::shared_ptr<Resource> _resource)
	{
		_resources.push_back(_resource);
		std::cout << "Resource Added" << std::endl;
	}
}