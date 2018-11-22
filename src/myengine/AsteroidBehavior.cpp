#include "AsteroidBehavior.h"
#include "Entity.h"
#include "Transform.h"
#include "Environment.h"
#include "Collider.h"
#include "PlayerController.h"
#include "Environment.h"

namespace frontier
{
	void AsteroidBehavior::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		Copyable = true;
		//_parent.lock()->getComponent<Transform>()->setRotation(glm::vec3())

		glm::vec3 direction = glm::vec3(0.0f, getEnvironment()->getRandomBetweenTwoValues(0.0f, 360.0f), 0.0f);

		ForwardVector.x = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y));
		ForwardVector.y = sin(glm::radians(direction.x));
		ForwardVector.z = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y));

		forwardSpeed = getEnvironment()->getRandomBetweenTwoValues(1.0f, 3.0f);

		if (getEnvironment()->getRandomBetweenTwoValues(1.0f, 10.0f) > 5.0f)
		{
			rotateForce = forwardSpeed;
		}
		else
		{
			rotateForce = -forwardSpeed;
		}
	}

	void AsteroidBehavior::OnActivate()
	{
		glm::vec3 direction = glm::vec3(0.0f, getEnvironment()->getRandomBetweenTwoValues(0.0f, 360.0f), 0.0f);

		ForwardVector.x = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y));
		ForwardVector.y = sin(glm::radians(direction.x));
		ForwardVector.z = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y));

		forwardSpeed = getEnvironment()->getRandomBetweenTwoValues(1.0f, 5.0f);
	}

	void AsteroidBehavior::OnTick()
	{
		getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() + (ForwardVector * (-forwardSpeed * getEnvironment()->getDeltaTime())));

		getEntity()->getComponent<Transform>()->setRotation(getEntity()->getComponent<Transform>()->getRotation() + (glm::vec3(1.0f) * (rotateForce * getEnvironment()->getDeltaTime())));

		if (getEntity()->getComponent<Transform>()->getPosition().x > 80)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(-49, getEntity()->getComponent<Transform>()->getPosition().y, getEntity()->getComponent<Transform>()->getPosition().z));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().x < -80)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(49, getEntity()->getComponent<Transform>()->getPosition().y, getEntity()->getComponent<Transform>()->getPosition().z));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().z > 70)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(getEntity()->getComponent<Transform>()->getPosition().x, getEntity()->getComponent<Transform>()->getPosition().y, -39));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().z < -70)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(getEntity()->getComponent<Transform>()->getPosition().x, getEntity()->getComponent<Transform>()->getPosition().y, 39));
		}

		if (getEntity()->getComponent<Collider>()->isColliding())
		{
			std::vector<std::weak_ptr<Entity>> _collidingEntities = getEntity()->getComponent<Collider>()->getCollidingEntities();
			for (size_t i = 0; i < _collidingEntities.size(); i++)
			{
				if (_collidingEntities[i].lock()->hasComponent<PlayerController>())
				{
					//getEntity()->setActive(false);
				}
			}
		}


	}




}