#include "Resource.h"
#include <iostream>

namespace frontier
{

	Resource::Resource()
	{
		std::cout << "Resource Created" << std::endl;
	}

	Resource::Resource(std::string _pathStr)
	{
		_path = _pathStr;
	}

	Resource::~Resource()
	{
		std::cout << "Resource Destroyed" << std::endl;
	}

}