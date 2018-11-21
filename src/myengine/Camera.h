#include "glm.hpp"
#include "Component.h"

namespace frontier
{
	class Transform;

	class Camera: public Component
	{
	public:
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		glm::mat4 getOrthographicMatrix();
		using Component::OnInit;
		void OnInit(std::weak_ptr<Entity> _parent, float fov, float near, float far);
		bool getMain();
		void setMain(bool main);
		void setControllable(bool _control);
		void OnTick() override;

	private:
		bool _controlable;
		bool _main;
		float _FOV;
		float _near;
		float _far;
		bool moveForward, moveLeft, moveRight, moveBack, lockUpMovement, lockDownMovement;
		float _lastx, _lasty, _sensitivity, _pitch, _yaw, _controllerRotationForce;
		std::weak_ptr<Transform> target;
	};
}