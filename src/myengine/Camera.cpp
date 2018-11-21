#include "Camera.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Input.h"
#include "Environment.h"
#include "Timer.h"
#include <SDL2/SDL_keycode.h>
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

namespace frontier
{
	glm::mat4 Camera::getViewMatrix()
	{
		glm::mat4 view;

		view = glm::inverse(getEntity()->getComponent<Transform>()->getModelMatrix());

		return view;
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		glm::mat4 proj = glm::perspective(glm::radians(_FOV), (float)getCore()->getWidth() / (float)getCore()->getHeight(), _near, _far);
		return proj;
	}

	glm::mat4 Camera::getOrthographicMatrix()
	{
		glm::mat4 orth = glm::ortho(0.0f, (float)getCore()->getWidth(), 0.0f, (float)getCore()->getHeight(), 0.1f, 100.0f);
		return orth;
	}

	void Camera::OnInit(std::weak_ptr<Entity> _parent, float fov, float near, float far)
	{
		Component::OnInit(_parent);
		_FOV = fov;
		_near = near;
		_far = far;
		_lastx = 320;
		_lasty = 240;
		_sensitivity = 0.5f;
		_pitch = 0.0f;
		_yaw = -90.0f;
		_controllerRotationForce = 10.0f;
	}

	bool Camera::getMain()
	{
		return _main;
	}

	void Camera::setMain(bool main)
	{
		_main = main;
	}

	void Camera::setControllable(bool _control)
	{
		_controlable = _control;
	}

	void Camera::OnTick()
	{

	}

}