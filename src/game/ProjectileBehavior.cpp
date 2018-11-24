#include "ProjectileBehavior.h"
#include "PlayerController.h"



void ProjectileBehavior::OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<frontier::Entity> _player)
{
	Component::OnInit(_parent);
	player = _player;
	speed = 8.0f;
}

void ProjectileBehavior::OnInit(std::weak_ptr<frontier::Entity> _parent, std::weak_ptr<ProjectileBehavior> _original)
{
	Component::OnInit(_parent);
	player = _original.lock()->GetPlayer();
	speed = 8.0f;
}

void ProjectileBehavior::OnTick()
{
	getEntity()->getComponent<frontier::Transform>()->setPosition(getEntity()->getComponent<frontier::Transform>()->getPosition() + (forwardVector * (-speed * getEnvironment()->getDeltaTime())));

	if (getEntity()->getComponent<frontier::Transform>()->getPosition().x > 50 || getEntity()->getComponent<frontier::Transform>()->getPosition().x < -50 || getEntity()->getComponent<frontier::Transform>()->getPosition().z > 40 || getEntity()->getComponent<frontier::Transform>()->getPosition().z < -40)
	{
		getEntity()->setActive(false);
	}

}

void ProjectileBehavior::OnActivate()
{
	getEntity()->getComponent<frontier::Transform>()->setPosition(player.lock()->getComponent<frontier::Transform>()->getPosition());
	forwardVector = player.lock()->getComponent<PlayerController>()->getForwardVector();
}

std::weak_ptr<frontier::Entity> ProjectileBehavior::GetPlayer()
{
	return player;
}
