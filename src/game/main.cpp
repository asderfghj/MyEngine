#include <iostream>
#include <memory>
#include <myengine/Core.h>
#include <myengine/Entity.h>
#include <myengine/Component.h>

int main()
{

	std::shared_ptr<Core> _core = std::make_shared<Core>();
	_core->SetSelf(_core);

	std::shared_ptr<Entity> _entity1 = _core->addEntity();

	_entity1->setSelf(_entity1);

	_entity1->addComponent<Component>();


	std::cout << "Program Start" << std::endl;
	_core->Start();

	std::cout << "Program Ended" << std::endl;
	std::cin.get();
	
	return 0;
}