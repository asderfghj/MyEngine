#include "Component.h"
#include "glm.hpp"


namespace myengine
{
	class Entity;


	class PlayerController : public Component
	{
	public:
		void OnInit(std::weak_ptr<Entity> _parent);
		void OnTick() override;

	private:

		float RotateVelocity, ForwardVelocity, RotateFade, ForwardFade, RotateIncreaseAmount, ForwardIncreaseAmount, ForwardVelocityCap, RotateVelocityCap; 
		glm::vec3 forwardVector;

	};

}