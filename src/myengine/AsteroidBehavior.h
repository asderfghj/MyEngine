#include "Component.h"
#include "glm.hpp"

namespace frontier
{

	class AsteroidBehavior: public Component
	{
	private:
		glm::vec3 ForwardVector;
		float forwardSpeed;
		float rotateForce;
		bool randomiserOverride = false;

	public:
		void OnInit(std::weak_ptr<Entity> _parent);
		void OnTick() override;
		void OnActivate() override;
		void SetDirection(glm::vec3 newDirection);
		void setRandomiserOverride(bool _override);
	};





}