#include "Component.h"
#include "glm.hpp"


namespace frontier
{
	class Entity;


	class PlayerController : public Component
	{
	public:
		void OnInit(std::weak_ptr<Entity> _parent);
		void OnTick() override;
		glm::vec3 getForwardVector();


	private:

		float RotateVelocity, ForwardVelocity, RotateFade, ForwardFade, RotateIncreaseAmount, ForwardIncreaseAmount, ForwardVelocityCap, RotateVelocityCap; 
		glm::vec3 forwardVector;
		bool shooting, hasshot;
		int shotCooldownTime, countedFrames;

	};

}