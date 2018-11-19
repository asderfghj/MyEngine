#include "glm.hpp"
#include "Component.h"

namespace myengine
{
	class Transform;

	class Camera: public Component
	{
	public:
		glm::mat4 getViewMatrix();
		glm::mat4 getProjectionMatrix();
		using Component::OnInit;
		void OnInit(std::weak_ptr<Entity> _parent, float fov, float near, float far);
		bool getMain();
		void setMain(bool main);
		void setControllable(bool _control);
		void OnTick() override;
		void setTarget(std::weak_ptr<Transform> _target);

	private:
		bool _controlable;
		bool _main;
		float _FOV;
		float _near;
		float _far;
		float _cameraRangeLock;
		glm::vec3 camFront;
		glm::vec3 camUp;
		bool moveForward, moveLeft, moveRight, moveBack, lockUpMovement, lockDownMovement;
		float _lastx, _lasty, _sensitivity, _pitch, _yaw, _controllerRotationForce;
		std::weak_ptr<Transform> target;
	};
}