#include "Component.h"
#include "glm.hpp"


namespace frontier
{
	class Entity;

	class ProjectileBehavior : public Component
	{
	public:
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Entity> _player);
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<ProjectileBehavior> _original);
		void OnTick() override;
		void OnActivate() override;
		std::weak_ptr<Entity> GetPlayer();

	private:
		glm::vec3 forwardVector;
		float speed;
		std::weak_ptr<Entity> player;
	};
}