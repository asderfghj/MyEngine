#include <iostream>
#include <memory>
#include <myengine/MyEngine.h>
#include <exception>
#include "ProjectileBehavior.h"
#include "PlayerController.h"
#include "AsteroidBehavior.h"
#include "AsteroidSpawner.h"


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
	std::shared_ptr<frontier::Shader> DefaultModelShader = frontier::Shader::Create("../resources/fragmentshaders/fragmenttest.fs", "../resources/vertexshaders/vertextest.vs", { "aPos", "aNormal", "aTexCoords" }, _core->getResources());

	std::shared_ptr<frontier::Texture> Fightertexture = frontier::Texture::Create("../resources/textures/fighter.png", _core->getResources(), 1);

	std::shared_ptr<frontier::Texture> AsteroidTexture = frontier::Texture::Create("../resources/textures/astroid.jpg", _core->getResources(), 3);

	std::shared_ptr<frontier::Texture> MissileTexture = frontier::Texture::Create("../resources/textures/green.png", _core->getResources(), 5);

	std::shared_ptr<frontier::Texture> LivesImage = frontier::Texture::Create("../resources/textures/livesicon.png", _core->getResources(), 4);

	std::shared_ptr<frontier::Texture> GameOverTextImage = frontier::Texture::Create("../resources/textures/GameOverText.png", _core->getResources(), 6);

	std::shared_ptr<frontier::Texture> GameOverBackgroundImage = frontier::Texture::Create("../resources/textures/backgroundtexture.png", _core->getResources(), 7);

	std::shared_ptr<frontier::Model> FighterModel = frontier::Model::Create("../resources/models/Fighter/fighter01.obj", _core->getResources());

	std::shared_ptr<frontier::Model> AsteroidModel = frontier::Model::Create("../resources/models/astroid/astroid.obj", _core->getResources());

	std::shared_ptr<frontier::Model> MissileModel = frontier::Model::Create("../resources/models/Missile.obj", _core->getResources());

	std::shared_ptr<frontier::Sound> shootsound = frontier::Sound::Create("../resources/sounds/laser.ogg", _core->getResources());

	std::shared_ptr<frontier::Sound> music = frontier::Sound::Create("../resources/sounds/music.ogg", _core->getResources());

	std::shared_ptr<frontier::Sound> crashSound = frontier::Sound::Create("../resources/sounds/crash.ogg", _core->getResources());

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

	//skybox
	std::shared_ptr<frontier::Entity> skyBox = _core->addEntity();

	skyBox->addComponent<frontier::Skybox, std::shared_ptr<frontier::CubemapTexture>>(_cb1);

	//ui
	std::shared_ptr<frontier::Entity> livesIcon1 = _core->addUiElement(glm::vec2(25.0f, _core->getHeight() - 25.0f), 0.0f, glm::vec3(0.03f, 0.03f, 0.03f));

	livesIcon1->addComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(LivesImage, true);

	std::shared_ptr<frontier::Entity> livesIcon2 = _core->addUiElement(glm::vec2(60.0f, _core->getHeight() - 25.0f), 0.0f, glm::vec3(0.03f, 0.03f, 0.03f));

	livesIcon2->addComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(LivesImage, true);

	std::shared_ptr<frontier::Entity> livesIcon3 = _core->addUiElement(glm::vec2(95.0f, _core->getHeight() - 25.0f), 0.0f, glm::vec3(0.03f, 0.03f, 0.03f));

	livesIcon3->addComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(LivesImage, true);

	std::shared_ptr<frontier::Entity> gameOverText = _core->addUiElement(glm::vec2(_core->getWidth() / 2, _core->getHeight() / 2), 0.0f, glm::vec3(0.1f, 0.1f, 0.1f));

	gameOverText->addComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(GameOverTextImage, true);

	gameOverText->setActive(false);

	//player
	std::shared_ptr<frontier::Entity> _Player = _core->addEntity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f, 0.7f, 0.7f));

	_Player->addComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(FighterModel);

	_Player->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_Player->getComponent<frontier::MeshRenderer>()->AttachTexture(Fightertexture);

	_Player->addComponent<PlayerController>();

	_Player->getComponent<PlayerController>()->setUIIcons(livesIcon1, livesIcon2, livesIcon3, gameOverText);

	std::shared_ptr<frontier::AudioPlayer> shootSoundComponent = _Player->addComponent<frontier::AudioPlayer, std::shared_ptr<frontier::Sound>>(shootsound);

	std::shared_ptr<frontier::AudioPlayer> crashSoundComponent = _Player->addComponent<frontier::AudioPlayer, std::shared_ptr<frontier::Sound>>(crashSound);

	_Player->getComponent<PlayerController>()->setAudioPlayers(shootSoundComponent, crashSoundComponent);

	_Player->addComponent<frontier::Collider, glm::vec3>(glm::vec3(2.0f, 2.0f, 2.0f));

	//music player
	std::shared_ptr<frontier::Entity> _musicPlayer = _core->addEntity();

	_musicPlayer->addComponent<frontier::AudioPlayer, std::shared_ptr<frontier::Sound>>(music);

	//prefab initialisation 
	std::shared_ptr<frontier::Prefab> _asteroidPrefab = _core->addPrefab();

	_asteroidPrefab->addComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(AsteroidModel);

	_asteroidPrefab->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_asteroidPrefab->getComponent<frontier::MeshRenderer>()->AttachTexture(AsteroidTexture);

	_asteroidPrefab->addComponent<frontier::Collider, glm::vec3>(glm::vec3(20.0f, 20.0f, 20.0f));

	_asteroidPrefab->addComponent<AsteroidBehavior>();

	std::shared_ptr<frontier::Prefab> _missilePrefab = _core->addPrefab();

	_missilePrefab->addComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(MissileModel);

	_missilePrefab->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_missilePrefab->getComponent<frontier::MeshRenderer>()->AttachTexture(MissileTexture);

	_missilePrefab->addComponent<frontier::Collider, glm::vec3>(glm::vec3(0.6f, 0.6f, 0.6f));

	_missilePrefab->addComponent<ProjectileBehavior, std::weak_ptr<frontier::Entity>>(_Player);

	std::shared_ptr<frontier::Entity> _asteroidSpawner = _core->addEntity();

	//poolers
	_core->addPooler("missilepooler", _missilePrefab, 8);

	_core->addPooler("asteroidpooler", _asteroidPrefab, 8);

	_asteroidSpawner->addComponent<AsteroidSpawner, std::weak_ptr<frontier::Pooler>>(_core->getPooler("asteroidpooler"));

	_asteroidSpawner->getComponent<AsteroidSpawner>()->SetPlayer(_Player);

	//camera positioning
	_core->getMainCamera()->getEntity()->getComponent<frontier::Transform>()->setPosition(glm::vec3(0.0f, 90.0f, 0.0f));
	_core->getMainCamera()->getEntity()->getComponent<frontier::Transform>()->setRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	_musicPlayer->getComponent<frontier::AudioPlayer>()->Play(true);

	//start button
	std::cout << "Program Start" << std::endl;
	_core->Start();

	std::cout << "Program Ended" << std::endl;
}