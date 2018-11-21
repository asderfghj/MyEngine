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
	std::shared_ptr<frontier::Core> _core = std::make_shared<frontier::Core>();

	_core->Init(_core, 1000, 800);

	

	std::shared_ptr<frontier::Shader> _shader1 = frontier::Shader::Create("../resources/fragmentshaders/fragmenttest.fs", "../resources/vertexshaders/vertextest.vs", { "in_Position" }, _core->getResources());

	std::shared_ptr<frontier::Shader> _shader2 = frontier::Shader::Create("../resources/fragmentshaders/tritest.fs", "../resources/vertexshaders/tritest.vs", { "in_Position" }, _core->getResources());

	std::shared_ptr<frontier::Texture> _texture1 = frontier::Texture::Create("../resources/textures/fighter.png", _core->getResources(), 1);

	std::shared_ptr<frontier::Texture> _texture2 = frontier::Texture::Create("../resources/textures/astroid.jpg", _core->getResources(), 3);

	std::shared_ptr<frontier::Texture> _texture3 = frontier::Texture::Create("../resources/textures/livestrans.png", _core->getResources(), 4);

	std::shared_ptr<frontier::Model> _model1 = frontier::Model::Create("../resources/models/Fighter/fighter01.obj", _core->getResources());

	std::shared_ptr<frontier::Model> _model2 = frontier::Model::Create("../resources/models/astroid/astroid.obj", _core->getResources());

	std::vector<std::string> faces =
	{
		"../resources/textures/skybox/right.png",
		"../resources/textures/skybox/left.png",
		"../resources/textures/skybox/top.png",
		"../resources/textures/skybox/bot.png",
		"../resources/textures/skybox/front.png",
		"../resources/textures/skybox/back.png",
	};

	std::shared_ptr<frontier::CubemapTexture> _cb1 = frontier::CubemapTexture::Create(faces, _core->getResources(), 2);

	//entity 4
	std::shared_ptr<frontier::Entity> _uiTester = _core->addUiElement(glm::vec3(_core->getWidth() / 2, _core->getHeight() / 2, -5.0f), 0.0f, glm::vec3(30.0f, 30.0f, 30.0f));

	_uiTester->addComponent<frontier::UIImage>();

	_uiTester->getComponent<frontier::UIImage>()->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));

	_uiTester->addComponent<frontier::UIButton>();

	_uiTester->getComponent<frontier::UIButton>()->setidleColor(glm::vec3(1.0f, 0.0f, 0.0f));

	_uiTester->getComponent<frontier::UIButton>()->setOverlapColor(glm::vec3(1.0f, 0.37f, 0.0f));

	_uiTester->getComponent<frontier::UIButton>()->setpressedColor(glm::vec3(0.0f, 1.0f, 0.0f));

	//entity 2, skybox
	std::shared_ptr<frontier::Entity> _entity2 = _core->addEntity();

	_entity2->addComponent<frontier::Skybox, std::shared_ptr<frontier::CubemapTexture>>(_cb1);

	//entity 1, player
	std::shared_ptr<frontier::Entity> _entity1 = _core->addEntity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f, 0.7f, 0.7f));

	_entity1->addComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(_model1);

	_entity1->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(_shader1);

	_entity1->getComponent<frontier::MeshRenderer>()->AttachTexture(_texture1);

	_entity1->addComponent<frontier::PlayerController>();

	_entity1->addComponent<frontier::Collider, glm::vec3>(glm::vec3(1.3f, 1.3f, 1.3f));

	//entity 3, asteroid
	std::shared_ptr<frontier::Entity> _entity3 = _core->addEntity(glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f));

	_entity3->addComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(_model2);

	_entity3->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(_shader1);

	_entity3->getComponent<frontier::MeshRenderer>()->AttachTexture(_texture2);

	_entity3->addComponent<frontier::Collider, glm::vec3>(glm::vec3(2.0f, 2.0f, 2.0f));



	_core->getMainCamera()->getEntity()->getComponent<frontier::Transform>()->setPosition(glm::vec3(0.0f, 90.0f, 0.0f));
	_core->getMainCamera()->getEntity()->getComponent<frontier::Transform>()->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));

	std::cout << "Program Start" << std::endl;
	_core->Start();

	std::cout << "Program Ended" << std::endl;
}