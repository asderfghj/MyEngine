#include <iostream>
#include <memory>
#include <myengine/MyEngine.h>
#include <exception>


void safe_main();

int main()
{
	try
	{
		safe_main();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
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
	std::shared_ptr<myengine::Core> _core = std::make_shared<myengine::Core>();


	_core->SetSelf(_core);

	std::shared_ptr<myengine::Shader> _shader1 = myengine::Shader::Create("../resources/fragmentshaders/fragmenttest.fs", "../resources/vertexshaders/vertextest.vs", { "in_Position" }, _core->getResources());

	std::shared_ptr<myengine::Texture> _texture1 = myengine::Texture::Create("../resources/textures/fighter.png", _core->getResources(), 1);

	std::shared_ptr<myengine::Model> _model1 = myengine::Model::Create("../resources/models/Fighter/fighter01.obj", _core->getResources());

	std::vector<std::string> faces =
	{
		"../resources/textures/skybox/right.png",
		"../resources/textures/skybox/left.png",
		"../resources/textures/skybox/top.png",
		"../resources/textures/skybox/bot.png",
		"../resources/textures/skybox/front.png",
		"../resources/textures/skybox/back.png",
	};

	std::shared_ptr<myengine::CubemapTexture> _cb1 = myengine::CubemapTexture::Create(faces, _core->getResources(), 2);



	//entity 2, skybox
	std::shared_ptr<myengine::Entity> _entity2 = _core->addEntity();

	_entity2->setSelf(_entity2);

	_entity2->addComponent<myengine::Skybox, std::shared_ptr<myengine::CubemapTexture>>(_cb1);

	//entity 1, player
	std::shared_ptr<myengine::Entity> _entity1 = _core->addEntity();

	_entity1->setSelf(_entity1);

	_entity1->addComponent<myengine::MeshRenderer, std::shared_ptr<myengine::Model>>(_model1);

	_entity1->getComponent<myengine::MeshRenderer>()->AttachShaderProgram(_shader1);

	_entity1->getComponent<myengine::MeshRenderer>()->AttachTexture(_texture1);

	_core->getMainCamera()->setTarget(_entity1->getComponent<myengine::Transform>());

	std::cout << "Program Start" << std::endl;
	_core->Start();

	std::cout << "Program Ended" << std::endl;
}