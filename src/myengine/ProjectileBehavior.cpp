#include "ProjectileBehavior.h"
#include "Entity.h"
#include "Transform.h"
#include "Environment.h"
#include "PlayerController.h"


namespace frontier
{
	void ProjectileBehavior::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Entity> _player)
	{
		Component::OnInit(_parent);
		player = _player;
		speed = 8.0f;
	}

	void ProjectileBehavior::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<ProjectileBehavior> _original)
	{
		Component::OnInit(_parent);
		player = _original.lock()->GetPlayer();
		speed = 8.0f;
	}

	void ProjectileBehavior::OnTick()
	{
		getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() + (forwardVector * (-speed * getEnvironment()->getDeltaTime())));

		if (getEntity()->getComponent<Transform>()->getPosition().x > 50 || getEntity()->getComponent<Transform>()->getPosition().x < -50 || getEntity()->getComponent<Transform>()->getPosition().z > 40 || getEntity()->getComponent<Transform>()->getPosition().z < -40)
		{
			getEntity()->setActive(false);
		}

		/*if (getEntity()->getComponent<Transform>()->getPosition().x < -50)
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
		}*/

	}

	void ProjectileBehavior::OnActivate()
	{
		getEntity()->getComponent<Transform>()->setPosition(player.lock()->getComponent<Transform>()->getPosition());
		forwardVector = player.lock()->getComponent<PlayerController>()->getForwardVector();
	}

	std::weak_ptr<Entity> ProjectileBehavior::GetPlayer()
	{
		return player;
	}
}