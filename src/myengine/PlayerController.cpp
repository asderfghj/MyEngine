#include "PlayerController.h"
#include "Entity.h"
#include "Input.h"
#include "Environment.h"
#include "Transform.h"

namespace myengine
{
	void PlayerController::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		RotateVelocity = 0.0f;
		ForwardVelocity = 0.0f;
		RotateFade = 0.1f;
		ForwardFade = 0.1f;
		RotateIncreaseAmount = 0.3f;
		ForwardIncreaseAmount = 0.2f;
		forwardVector = glm::vec3(0.0f, 0.0f, -1.0f);
	}

	void PlayerController::OnTick()
	{
		bool moveForward, rotateLeft, rotateRight;

		moveForward = getInput()->GetJoystickAxis(Input::LEFTSTICK).y < -8000;
		rotateLeft = getInput()->GetJoystickAxis(Input::LEFTSTICK).x < -8000;
		rotateRight = getInput()->GetJoystickAxis(Input::LEFTSTICK).x > 8000;

		if (moveForward)
		{
			ForwardVelocity += ForwardIncreaseAmount;
		}

		if (rotateLeft)
		{
			RotateVelocity -= RotateIncreaseAmount;
		}
		else if (rotateRight)
		{
			RotateVelocity += RotateIncreaseAmount;
		}

		if (ForwardVelocity > 0)
		{
			ForwardVelocity -= ForwardFade;
		}
		if (ForwardVelocity < 0)
		{
			ForwardVelocity = 0;
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

		if (RotateVelocity > 0 || RotateVelocity < 0)
		{
			glm::vec3 rotation = getEntity()->getComponent<Transform>()->getRotation();
			getEntity()->getComponent<Transform>()->setRotation(glm::vec3(rotation.x, rotation.y + (RotateVelocity * getEnvironment()->getDeltaTime()), rotation.z));

			forwardVector.x = cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x)) * cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().y));
			forwardVector.y = sin(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x));
			forwardVector.z = cos(glm::radians(getEntity()->getComponent<Transform>()->getRotation().x)) * sin(glm::radians(getEntity()->getComponent<Transform>()->getRotation().y));
			forwardVector = glm::normalize(forwardVector);

			std::cout << "Ship Forward Vector, x: " << forwardVector.x << " | y: " << forwardVector.y << " | z: " << forwardVector.z << std::endl;

		}

		

		if (ForwardVelocity > 0)
		{
			glm::vec3 position = getEntity()->getComponent<Transform>()->getPosition();
			getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() + (forwardVector * (ForwardVelocity * getEnvironment()->getDeltaTime())));
		}



	}
}