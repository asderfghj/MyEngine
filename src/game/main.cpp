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


	//resource initialisation
	std::shared_ptr<frontier::Shader> DefaultModelShader = frontier::Shader::Create("../resources/fragmentshaders/fragmenttest.fs", "../resources/vertexshaders/vertextest.vs", { "in_Position" }, _core->getResources());

	std::shared_ptr<frontier::Texture> Fightertexture = frontier::Texture::Create("../resources/textures/fighter.png", _core->getResources(), 1);

	std::shared_ptr<frontier::Texture> AsteroidTexture = frontier::Texture::Create("../resources/textures/astroid.jpg", _core->getResources(), 3);

	std::shared_ptr<frontier::Texture> LivesImage = frontier::Texture::Create("../resources/textures/livestrans.png", _core->getResources(), 4);

	std::shared_ptr<frontier::Model> FighterModel = frontier::Model::Create("../resources/models/Fighter/fighter01.obj", _core->getResources());

	std::shared_ptr<frontier::Model> AsteroidModel = frontier::Model::Create("../resources/models/astroid/astroid.obj", _core->getResources());

	std::shared_ptr<frontier::Model> LaserModel = frontier::Model::Create("../resources/models/Missile.obj", _core->getResources());

	std::vector<std::string> faces =
	{
		"../resources/textures/skybox/right.png",
		"../resources/textures/skybox/left.png",
		"../resources/textures/skybox/top.png",
		"../resources/textures/skybox/bot.png",
		"../resources/textures/skybox/front.png",
		"../resources/textures/skybox/back.png",
	};


	//prefab initialisation 
	std::shared_ptr<frontier::CubemapTexture> _cb1 = frontier::CubemapTexture::Create(faces, _core->getResources(), 2);

	std::shared_ptr<frontier::Entity> skyBox = _core->addEntity();

	skyBox->addComponent<frontier::Skybox, std::shared_ptr<frontier::CubemapTexture>>(_cb1);

	std::shared_ptr<frontier::Prefab> _asteroidPrefab = _core->addPrefab();

	_asteroidPrefab->addComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(AsteroidModel);

	_asteroidPrefab->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_asteroidPrefab->getComponent<frontier::MeshRenderer>()->AttachTexture(AsteroidTexture);

	_asteroidPrefab->addComponent<frontier::Collider, glm::vec3>(glm::vec3(2.0f, 2.0f, 2.0f));

	_asteroidPrefab->addComponent<frontier::AsteroidBehavior>();

	std::shared_ptr<frontier::Prefab> _laserPrefab;

	//player
	std::shared_ptr<frontier::Entity> _Player = _core->addEntity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f, 0.7f, 0.7f));

	_Player->addComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(FighterModel);

	_Player->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_Player->getComponent<frontier::MeshRenderer>()->AttachTexture(Fightertexture);

	_Player->addComponent<frontier::PlayerController>();

	_Player->addComponent<frontier::Collider, glm::vec3>(glm::vec3(1.3f, 1.3f, 1.3f));

	//asteroids
	std::shared_ptr<frontier::Entity> _asteroid1 = _core->addEntity(_asteroidPrefab, glm::vec3(0.0f, 0.0f, -15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.1f, 0.1f, 0.1f));

	std::shared_ptr<frontier::Entity> _asteroid2 = _core->addEntity(_asteroidPrefab, glm::vec3(15.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.2f, 0.2f, 0.2f));

	std::shared_ptr<frontier::Entity> _asteroid3 = _core->addEntity(_asteroidPrefab, glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.05f, 0.05f, 0.05f));

	std::shared_ptr<frontier::Entity> _asteroid4 = _core->addEntity(_asteroidPrefab, glm::vec3(-15.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.3f, 0.3f, 0.3f));

	//camera positioning
	_core->getMainCamera()->getEntity()->getComponent<frontier::Transform>()->setPosition(glm::vec3(0.0f, 90.0f, 0.0f));
	_core->getMainCamera()->getEntity()->getComponent<frontier::Transform>()->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));


	//start button
	std::cout << "Program Start" << std::endl;
	_core->Start();

	std::cout << "Program Ended" << std::endl;
}