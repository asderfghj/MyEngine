#ifndef RESOURCE_H_
#define RESOURCE_H_

#include <string>
#include <memory>

namespace frontier
{

	class Resource
	{
	protected:
		std::string _path;
	public:
		Resource();
		Resource(std::string _pathStr);
		~Resource();
	};

}
#endif // !