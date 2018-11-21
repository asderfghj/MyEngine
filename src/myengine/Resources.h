#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <list>
#include <memory>
#include "Resource.h"

namespace frontier
{

	class Resources
	{
	private:
		std::list<std::shared_ptr<Resource>> _resources;
		//need to add some cleanup functions here

	public:
		Resources();
		~Resources();
		void AddCreatedResource(std::shared_ptr<Resource> _resource);
	};
}

#endif // !RESOURCES_H_