#include "PlayerController.h"
#include "myengine/MyEngine.h"


void PlayerController::OnInit(std::weak_ptr<frontier::Entity> _parent)
{
	Component::OnInit(_parent);
	RotateVelocity = 0.0f;
	RotateVelocityCap = 10.0f;
	ForwardVelocity = 0.0f;
	ForwardVelocityCap = 5.0f;
	RotateFade = 0.1f;
	ForwardFade = 0.05f;
	RotateIncreaseAmount = 0.3f;
	ForwardIncreaseAmount = 0.2f;
	shotCooldownTime = 15;
	countedFrames = 0;
	life = 3;
	gameOver = false;
	forwardVector.x = cos(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().x)) * sin(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().y));
	forwardVector.y = sin(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().x));
	forwardVector.z = cos(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().x)) * cos(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().y));
	forwardVector = glm::normalize(forwardVector);
}

void PlayerController::OnTick()
{
	bool moveForward, rotateLeft, rotateRight;

	if (getInput()->isJoystickConnected())
	{
		moveForward = getInput()->GetJoystickAxis(frontier::Input::LEFTSTICK).y < -8000;
		rotateLeft = getInput()->GetJoystickAxis(frontier::Input::LEFTSTICK).x < -8000;
		rotateRight = getInput()->GetJoystickAxis(frontier::Input::LEFTSTICK).x > 8000;
		shooting = getInput()->getJoystickButton(frontier::Input::A_BUTTON);
	}
	else
	{
		moveForward = getInput()->getKey(frontier::Input::FORWARD);
		rotateLeft = getInput()->getKey(frontier::Input::LEFT);
		rotateRight = getInput()->getKey(frontier::Input::RIGHT);
		shooting = getInput()->getKey(frontier::Input::SHOOT);
	}

	if (moveForward)
	{
		ForwardVelocity += ForwardIncreaseAmount;
	}

	if (rotateLeft)
	{
		RotateVelocity += RotateIncreaseAmount;
	}
	else if (rotateRight)
	{
		RotateVelocity -= RotateIncreaseAmount;
	}

	if (ForwardVelocity > 0)
	{
		ForwardVelocity -= ForwardFade;
	}
	if (ForwardVelocity < 0)
	{
		ForwardVelocity = 0;
	}
	if (ForwardVelocity > ForwardVelocityCap)
	{
		ForwardVelocity = ForwardVelocityCap;
	}

	if (RotateVelocity > 0)
	{
		RotateVelocity -= RotateFade;
	}
	if (RotateVelocity < 0)
	{
		RotateVelocity += RotateFade;
	}

	if ((RotateVelocity < 0.2f && RotateVelocity > -0.2f) && (!rotateLeft || !rotateRight))
	{
		RotateVelocity = 0;
	}

	if (RotateVelocity > RotateVelocityCap)
	{
		RotateVelocity = RotateVelocityCap;
	}
	if (RotateVelocity < -RotateVelocityCap)
	{
		RotateVelocity = -RotateVelocityCap;
	}

	if (RotateVelocity > 0 || RotateVelocity < 0)
	{
		glm::vec3 rotation = getEntity()->getComponent<frontier::Transform>()->getRotation();
		getEntity()->getComponent<frontier::Transform>()->setRotation(glm::vec3(rotation.x, rotation.y + (RotateVelocity * getEnvironment()->getDeltaTime()), rotation.z));



		forwardVector.x = cos(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().x)) * sin(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().y));
		forwardVector.y = sin(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().x));
		forwardVector.z = cos(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().x)) * cos(glm::radians(getEntity()->getComponent<frontier::Transform>()->getRotation().y));
		forwardVector = glm::normalize(forwardVector);

	}

	if (ForwardVelocity > 0)
	{
		getEntity()->getComponent<frontier::Transform>()->setPosition(getEntity()->getComponent<frontier::Transform>()->getPosition() + (forwardVector * (-ForwardVelocity * getEnvironment()->getDeltaTime())));
	}

	if (getEntity()->getComponent<frontier::Transform>()->getPosition().x > 50)
	{
		getEntity()->getComponent<frontier::Transform>()->setPosition(glm::vec3(-49, getEntity()->getComponent<frontier::Transform>()->getPosition().y, getEntity()->getComponent<frontier::Transform>()->getPosition().z));
	}

	if (getEntity()->getComponent<frontier::Transform>()->getPosition().x < -50)
	{
		getEntity()->getComponent<frontier::Transform>()->setPosition(glm::vec3(49, getEntity()->getComponent<frontier::Transform>()->getPosition().y, getEntity()->getComponent<frontier::Transform>()->getPosition().z));
	}

	if (getEntity()->getComponent<frontier::Transform>()->getPosition().z > 40)
	{
		getEntity()->getComponent<frontier::Transform>()->setPosition(glm::vec3( getEntity()->getComponent<frontier::Transform>()->getPosition().x, getEntity()->getComponent<frontier::Transform>()->getPosition().y, -39));
	}

	if (getEntity()->getComponent<frontier::Transform>()->getPosition().z < -40)
	{
		getEntity()->getComponent<frontier::Transform>()->setPosition(glm::vec3(getEntity()->getComponent<frontier::Transform>()->getPosition().x, getEntity()->getComponent<frontier::Transform>()->getPosition().y, 39));
	}

	if (shooting && !hasshot)
	{
		shootSound.lock()->PlayWithVariance(1.0f, 0.9f, 1.1f);
		getCore()->getPooler("missilepooler")->Spawn(getEntity()->getComponent<frontier::Transform>()->getPosition());
		hasshot = true;
		countedFrames = 0;
	}
	else if (hasshot)
	{
		countedFrames++;
		if (countedFrames > shotCooldownTime)
		{
			hasshot = false;
		}
	}

	if (isInvicible)
	{
		if (invincibleCounter >= invincibleCooldownTime)
		{
			invincibleCounter = 0;
			isInvicible = false;
		}
		else
		{
			invincibleCounter++;
		}
	}


}

glm::vec3 PlayerController::getForwardVector()
{
	return forwardVector;
}

void PlayerController::setUIIcons(std::weak_ptr<frontier::Entity> _icon1, std::weak_ptr<frontier::Entity> _icon2, std::weak_ptr<frontier::Entity> _icon3, std::weak_ptr<frontier::Entity> _gameOver)
{
	_lifeIcon1 = _icon1;
	_lifeIcon2 = _icon2;
	_lifeIcon3 = _icon3;
	_gameOverText = _gameOver;
}

void PlayerController::Hit()
{
	life--;
	crashSound.lock()->PlayWithVariance(1.0f, 0.9f, 1.1f);
	if (life >= 3)
	{
		_lifeIcon1.lock()->setActive(true);
		_lifeIcon2.lock()->setActive(true);
		_lifeIcon3.lock()->setActive(true);
		isInvicible = true;
	}
	else if (life == 2)
	{
		_lifeIcon1.lock()->setActive(true);
		_lifeIcon2.lock()->setActive(true);
		_lifeIcon3.lock()->setActive(false);
		isInvicible = true;
	}
	else if (life == 1)
	{
		_lifeIcon1.lock()->setActive(true);
		_lifeIcon2.lock()->setActive(false);
		_lifeIcon3.lock()->setActive(false);
		isInvicible = true;
	}
	else
	{
		_lifeIcon1.lock()->setActive(false);
		_lifeIcon2.lock()->setActive(false);
		_lifeIcon3.lock()->setActive(false);
		gameOver = true;
		getCore()->deactivateAllInstancesInPools();
		_gameOverText.lock()->setActive(true);
		getEntity()->setActive(false);
	}
}

void PlayerController::setAudioPlayers(std::weak_ptr<frontier::AudioPlayer> _shootSound, std::weak_ptr<frontier::AudioPlayer> _crashSound)
{
	shootSound = _shootSound;
	crashSound = _crashSound;
}

bool PlayerController::IsGameOver()
{
	return gameOver;
}

bool PlayerController::IsInvicible()
{
	return isInvicible;
}

