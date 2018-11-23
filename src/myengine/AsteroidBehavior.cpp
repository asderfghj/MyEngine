#include "AsteroidBehavior.h"
#include "Entity.h"
#include "Transform.h"
#include "Environment.h"
#include "Collider.h"
#include "PlayerController.h"
#include "Environment.h"
#include "Core.h"
#include "ProjectileBehavior.h"
#include "Pooler.h"

namespace frontier
{
	void AsteroidBehavior::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		Copyable = true;

		if (!randomiserOverride)
		{

			if (_parent.lock()->hasComponent<Transform>())
			{
				float scalar = _parent.lock()->getCore()->getEnvironment()->getRandomBetweenTwoValues(0.05f, 0.3f);

				getEntity()->getComponent<Transform>()->setScale(glm::vec3(scalar, scalar, scalar));
			}

			glm::normalize(ForwardVector);
		}

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

		if (!randomiserOverride)
		{
			glm::vec3 direction = glm::vec3(0.0f, getEnvironment()->getRandomBetweenTwoValues(0.0f, 360.0f), 0.0f);


			if (getEntity()->hasComponent<Transform>())
			{
				float scalar = getEntity()->getCore()->getEnvironment()->getRandomBetweenTwoValues(0.05f, 0.3f);

				getEntity()->getComponent<Transform>()->setScale(glm::vec3(scalar, scalar, scalar));
			}

			ForwardVector.x = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y));
			ForwardVector.y = sin(glm::radians(direction.x));
			ForwardVector.z = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y));

			glm::normalize(ForwardVector);

		}

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

	void AsteroidBehavior::OnTick()
	{

		getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() + (ForwardVector * (-forwardSpeed * getEnvironment()->getDeltaTime())));

		getEntity()->getComponent<Transform>()->setPosition(glm::vec3(getEntity()->getComponent<Transform>()->getPosition().x, 0.0f, getEntity()->getComponent<Transform>()->getPosition().z));

		getEntity()->getComponent<Transform>()->setRotation(getEntity()->getComponent<Transform>()->getRotation() + (glm::vec3(1.0f) * (rotateForce * getEnvironment()->getDeltaTime())));

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
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(getEntity()->getComponent<Transform>()->getPosition().x, getEntity()->getComponent<Transform>()->getPosition().y, -39));
		}

		if (getEntity()->getComponent<Transform>()->getPosition().z < -40)
		{
			getEntity()->getComponent<Transform>()->setPosition(glm::vec3(getEntity()->getComponent<Transform>()->getPosition().x, getEntity()->getComponent<Transform>()->getPosition().y, 39));
		}

		if (getEntity()->getComponent<Collider>()->isColliding())
		{
			std::vector<std::weak_ptr<Entity>> _collidingEntities = getEntity()->getComponent<Collider>()->getCollidingEntities();
			for (size_t i = 0; i < _collidingEntities.size(); i++)
			{
				if (_collidingEntities[i].lock()->hasComponent<ProjectileBehavior>())
				{
					_collidingEntities[i].lock()->setActive(false);
					if (getEntity()->getComponent<Transform>()->getScale().x > 0.1f)
					{
						glm::vec3 direction = glm::vec3(0.0f, getEnvironment()->getRandomBetweenTwoValues(0.0f, 360.0f), 0.0f);
						glm::vec3 newForwardVector;

						newForwardVector.x = cos(glm::radians(direction.x)) * sin(glm::radians(direction.y));
						newForwardVector.y = sin(glm::radians(direction.x));
						newForwardVector.z = cos(glm::radians(direction.x)) * cos(glm::radians(direction.y));

						glm::normalize(newForwardVector);

						std::weak_ptr<Entity> newAsteroid1 = getCore()->getPooler("asteroidpooler")->Spawn(getEntity()->getComponent<Transform>()->getPosition());
						newAsteroid1.lock()->getComponent<Transform>()->setScale(glm::vec3(getEntity()->getComponent<Transform>()->getScale().x / 2, getEntity()->getComponent<Transform>()->getScale().y / 2, getEntity()->getComponent<Transform>()->getScale().z / 2));
						newAsteroid1.lock()->getComponent<AsteroidBehavior>()->setRandomiserOverride(true);
						newAsteroid1.lock()->getComponent<AsteroidBehavior>()->SetDirection(newForwardVector);

						std::weak_ptr<Entity> newAsteroid2 = getCore()->getPooler("asteroidpooler")->Spawn(getEntity()->getComponent<Transform>()->getPosition());
						newAsteroid2.lock()->getComponent<Transform>()->setScale(glm::vec3(getEntity()->getComponent<Transform>()->getScale().x / 2, getEntity()->getComponent<Transform>()->getScale().y / 2, getEntity()->getComponent<Transform>()->getScale().z / 2));
						newAsteroid2.lock()->getComponent<AsteroidBehavior>()->setRandomiserOverride(true);
						newAsteroid2.lock()->getComponent<AsteroidBehavior>()->SetDirection(-newForwardVector);

						
					}

					randomiserOverride = false;
					getEntity()->setActive(false);
				}
			}
		}


	}

	void AsteroidBehavior::SetDirection(glm::vec3 _direction)
	{
		ForwardVector = _direction;
	}

	void AsteroidBehavior::setRandomiserOverride(bool _override)
	{
		randomiserOverride = _override;
	}
}