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
	std::shared_ptr<frontier::Shader> DefaultModelShader = frontier::Shader::Create("../resources/fragmentshaders/fragmenttest.fs", "../resources/vertexshaders/vertextest.vs", { "aPos", "aNormal", "aTexCoords" }, _core->GetResources());

	std::shared_ptr<frontier::Texture> Fightertexture = frontier::Texture::Create("../resources/textures/fighter.png", _core->GetResources(), 1);

	std::shared_ptr<frontier::Texture> AsteroidTexture = frontier::Texture::Create("../resources/textures/astroid.jpg", _core->GetResources(), 3);

	std::shared_ptr<frontier::Texture> MissileTexture = frontier::Texture::Create("../resources/textures/green.png", _core->GetResources(), 5);

	std::shared_ptr<frontier::Texture> LivesImage = frontier::Texture::Create("../resources/textures/livesicon.png", _core->GetResources(), 4);

	std::shared_ptr<frontier::Texture> GameOverTextImage = frontier::Texture::Create("../resources/textures/GameOverText.png", _core->GetResources(), 6);

	std::shared_ptr<frontier::Texture> GameOverBackgroundImage = frontier::Texture::Create("../resources/textures/backgroundtexture.png", _core->GetResources(), 7);

	std::shared_ptr<frontier::Model> FighterModel = frontier::Model::Create("../resources/models/Fighter/fighter01.obj", _core->GetResources());

	std::shared_ptr<frontier::Model> AsteroidModel = frontier::Model::Create("../resources/models/astroid/astroid.obj", _core->GetResources());

	std::shared_ptr<frontier::Model> MissileModel = frontier::Model::Create("../resources/models/Missile.obj", _core->GetResources());

	std::shared_ptr<frontier::Sound> shootsound = frontier::Sound::Create("../resources/sounds/laser.ogg", _core->GetResources());

	std::shared_ptr<frontier::Sound> music = frontier::Sound::Create("../resources/sounds/music.ogg", _core->GetResources());

	std::shared_ptr<frontier::Sound> crashSound = frontier::Sound::Create("../resources/sounds/crash.ogg", _core->GetResources());

	std::vector<std::string> faces =
	{
		"../resources/textures/skybox/right.png",
		"../resources/textures/skybox/left.png",
		"../resources/textures/skybox/top.png",
		"../resources/textures/skybox/bot.png",
		"../resources/textures/skybox/front.png",
		"../resources/textures/skybox/back.png",
	};

	std::shared_ptr<frontier::CubemapTexture> _cb1 = frontier::CubemapTexture::Create(faces, _core->GetResources(), 2);

	//skybox
	std::shared_ptr<frontier::Entity> skyBox = _core->AddEntity();

	skyBox->AddComponent<frontier::Skybox, std::shared_ptr<frontier::CubemapTexture>>(_cb1);

	//ui
	std::shared_ptr<frontier::Entity> livesIcon1 = _core->AddUIElement(glm::vec2(25.0f, _core->GetHeight() - 25.0f), 0.0f, glm::vec3(0.03f, 0.03f, 0.03f));

	livesIcon1->AddComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(LivesImage, true);

	std::shared_ptr<frontier::Entity> livesIcon2 = _core->AddUIElement(glm::vec2(60.0f, _core->GetHeight() - 25.0f), 0.0f, glm::vec3(0.03f, 0.03f, 0.03f));

	livesIcon2->AddComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(LivesImage, true);

	std::shared_ptr<frontier::Entity> livesIcon3 = _core->AddUIElement(glm::vec2(95.0f, _core->GetHeight() - 25.0f), 0.0f, glm::vec3(0.03f, 0.03f, 0.03f));

	livesIcon3->AddComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(LivesImage, true);

	std::shared_ptr<frontier::Entity> gameOverText = _core->AddUIElement(glm::vec2(_core->GetWidth() / 2, _core->GetHeight() / 2), 0.0f, glm::vec3(0.1f, 0.1f, 0.1f));

	gameOverText->AddComponent<frontier::UIImage, std::shared_ptr<frontier::Texture>, bool>(GameOverTextImage, true);

	gameOverText->SetActive(false);

	//player
	std::shared_ptr<frontier::Entity> _Player = _core->AddEntity(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.7f, 0.7f, 0.7f));

	_Player->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(FighterModel);

	_Player->getComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_Player->getComponent<frontier::MeshRenderer>()->AttachTexture(Fightertexture);

	_Player->AddComponent<PlayerController>();

	_Player->getComponent<PlayerController>()->setUIIcons(livesIcon1, livesIcon2, livesIcon3, gameOverText);

	std::shared_ptr<frontier::AudioPlayer> shootSoundComponent = _Player->AddComponent<frontier::AudioPlayer, std::shared_ptr<frontier::Sound>>(shootsound);

	std::shared_ptr<frontier::AudioPlayer> crashSoundComponent = _Player->AddComponent<frontier::AudioPlayer, std::shared_ptr<frontier::Sound>>(crashSound);

	_Player->getComponent<PlayerController>()->setAudioPlayers(shootSoundComponent, crashSoundComponent);

	_Player->AddComponent<frontier::Collider, glm::vec3>(glm::vec3(2.0f, 2.0f, 2.0f));

	//music player
	std::shared_ptr<frontier::Entity> _musicPlayer = _core->AddEntity();

	_musicPlayer->AddComponent<frontier::AudioPlayer, std::shared_ptr<frontier::Sound>>(music);

	//prefab initialisation 
	std::shared_ptr<frontier::Prefab> _asteroidPrefab = _core->AddPrefab();

	_asteroidPrefab->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(AsteroidModel);

	_asteroidPrefab->GetComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_asteroidPrefab->GetComponent<frontier::MeshRenderer>()->AttachTexture(AsteroidTexture);

	_asteroidPrefab->AddComponent<frontier::Collider, glm::vec3>(glm::vec3(20.0f, 20.0f, 20.0f));

	_asteroidPrefab->AddComponent<AsteroidBehavior>();

	std::shared_ptr<frontier::Prefab> _missilePrefab = _core->AddPrefab();

	_missilePrefab->AddComponent<frontier::MeshRenderer, std::shared_ptr<frontier::Model>>(MissileModel);

	_missilePrefab->GetComponent<frontier::MeshRenderer>()->AttachShaderProgram(DefaultModelShader);

	_missilePrefab->GetComponent<frontier::MeshRenderer>()->AttachTexture(MissileTexture);

	_missilePrefab->AddComponent<frontier::Collider, glm::vec3>(glm::vec3(0.6f, 0.6f, 0.6f));

	_missilePrefab->AddComponent<ProjectileBehavior, std::weak_ptr<frontier::Entity>>(_Player);

	std::shared_ptr<frontier::Entity> _asteroidSpawner = _core->AddEntity();

	//poolers
	_core->AddPooler("missilepooler", _missilePrefab, 8);

	_core->AddPooler("asteroidpooler", _asteroidPrefab, 8);

	_asteroidSpawner->AddComponent<AsteroidSpawner, std::weak_ptr<frontier::Pooler>>(_core->GetPooler("asteroidpooler"));

	_asteroidSpawner->getComponent<AsteroidSpawner>()->SetPlayer(_Player);

	//camera positioning
	_core->GetMainCamera()->GetEntity()->getComponent<frontier::Transform>()->SetPosition(glm::vec3(0.0f, 90.0f, 0.0f));
	_core->GetMainCamera()->GetEntity()->getComponent<frontier::Transform>()->SetRotation(glm::vec3(-90.0f, 0.0f, 0.0f));
	_musicPlayer->getComponent<frontier::AudioPlayer>()->Play(true);

	_core->Start();

}