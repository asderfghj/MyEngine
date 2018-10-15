#include <iostream>
#include <memory>
#include <myengine/Core.h>
#include <myengine/Entity.h>
#include <myengine/TriangleRenderer.h>

void safe_main();

int main()
{
	try
	{
		safe_main();
	}
	catch (...)
	{
		std::cout << "Something went wrong" << std::endl;
	}

	std::cin.get();
	
	return 0;
}

void safe_main()
{
	std::shared_ptr<Core> _core = std::make_shared<Core>();

	std::cout << "Core Added and initialised" << std::endl;

	_core->SetSelf(_core);

	std::cout << "Entity Added" << std::endl;

	std::shared_ptr<Entity> _entity1 = _core->addEntity();

	std::cout << "Entity Added" << std::endl;

	_entity1->setSelf(_entity1);

	std::shared_ptr<TriangleRenderer> triRen = _entity1->addComponent<TriangleRenderer>();



	std::cout << "Program Start" << std::endl;
	_core->Start();

	std::cout << "Program Ended" << std::endl;
}