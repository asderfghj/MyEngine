#include "PlayerController.h"
#include "Entity.h"
#include "Input.h"
#include "Environment.h"
#include "Transform.h"
#include "Collider.h"
#include "Core.h"
#include "Pooler.h"
#include "AudioPlayer.h"

namespace frontier
{
	void PlayerController::OnInit(std::weak_ptr<Entity> _parent)
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
		forwardVector.x = cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x)) * sin(glm::radians(getEntity()->getComponent<Transform>()->getRotation().y));
		forwardVector.y = sin(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x));
		forwardVector.z = cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x)) * cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().y));
		forwardVector = glm::normalize(forwardVector);
	}

	void PlayerController::OnTick()
	{
		bool moveForward, rotateLeft, rotateRight;

		if (getInput()->isJoystickConnected())
		{
			moveForward = getInput()->GetJoystickAxis(Input::LEFTSTICK).y < -8000;
			rotateLeft = getInput()->GetJoystickAxis(Input::LEFTSTICK).x < -8000;
			rotateRight = getInput()->GetJoystickAxis(Input::LEFTSTICK).x > 8000;
			shooting = getInput()->getJoystickButton(Input::A_BUTTON);
		}
		else
		{
			moveForward = getInput()->getKey(Input::FORWARD);
			rotateLeft = getInput()->getKey(Input::LEFT);
			rotateRight = getInput()->getKey(Input::RIGHT);
			shooting = getInput()->getKey(Input::SHOOT);
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
			glm::vec3 rotation = getEntity()->getComponent<Transform>()->getRotation();
			getEntity()->getComponent<Transform>()->setRotation(glm::vec3(rotation.x, rotation.y + (RotateVelocity * getEnvironment()->getDeltaTime()), rotation.z));



			forwardVector.x = cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x)) * sin(glm::radians(getEntity()->getComponent<Transform>()->getRotation().y));
			forwardVector.y = sin(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x));
			forwardVector.z = cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x)) * cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().y));
			forwardVector = glm::normalize(forwardVector);

		}

		if (ForwardVelocity > 0)
		{
			getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() + (forwardVector * (-ForwardVelocity * getEnvironment()->getDeltaTime())));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().x > 50)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(-49, getEntity()->getComponent<Transform>()->getPosition().y, getEntity()->getComponent<Transform>()->getPosition().z));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().x < -50)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(49, getEntity()->getComponent<Transform>()->getPosition().y, getEntity()->getComponent<Transform>()->getPosition().z));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().z > 40)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3( getEntity()->getComponent<Transform>()->getPosition().x, getEntity()->getComponent<Transform>()->getPosition().y, -39));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().z < -40)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(getEntity()->getComponent<Transform>()->getPosition().x, getEntity()->getComponent<Transform>()->getPosition().y, 39));
		}

		//std::cout << "player pos: " << getEntity()->getComponent<Transform>()->getPosition().x << " " << getEntity()->getComponent<Transform>()->getPosition().y << " " << getEntity()->getComponent<Transform>()->getPosition().z << std::endl;

		std::cout << "player rotation: " << getEntity()->getComponent<Transform>()->getRotation().x << " " << getEntity()->getComponent<Transform>()->getRotation().y << " " << getEntity()->getComponent<Transform>()->getRotation().z << std::endl;


		//std::cout << "player forward: " << forwardVector.x << " " << forwardVector.y << " " << forwardVector.z << std::endl;

		if (shooting && !hasshot)
		{
			getEntity()->getComponent<AudioPlayer>()->Play();
			getCore()->getPooler("missilepooler")->Spawn(getEntity()->getComponent<Transform>()->getPosition());
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


	}

	glm::vec3 PlayerController::getForwardVector()
	{
		return forwardVector;
	}
}