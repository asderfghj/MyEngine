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

namespace myengine
{
	glm::mat4 Camera::getViewMatrix()
	{
		glm::mat4 view;
		glm::vec3 camPos = getEntity()->getComponent<Transform>()->getPosition();
		view = glm::lookAt(camPos, camPos + camFront, camUp);
		//if (_isTargetingOtherTransform)
		//{
		//	view = view * target.lock()->getPositionMatrix();
		//}
		return view;
	}

	glm::mat4 Camera::getProjectionMatrix()
	{
		glm::mat4 proj = glm::perspective(glm::radians(_FOV), (float)getCore()->getWidth() / (float)getCore()->getHeight(), _near, _far);
		//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 640.0f / 480.0f, 0.1f, 100.0f);
		return proj;
	}

	void Camera::OnInit(std::weak_ptr<Entity> _parent, float fov, float near, float far)
	{
		Component::OnInit(_parent);
		_FOV = fov;
		_near = near;
		_far = far;
		camFront = glm::vec3(0.0f, 0.0f, -1.0f);
		camUp = glm::vec3(0.0f, 1.0f, 0.0f);
		_lastx = 320;
		_lasty = 240;
		_sensitivity = 0.5f;
		_pitch = 0.0f;
		_yaw = -90.0f;
		_controllerRotationForce = 10.0f;
		_cameraRangeLock = 3.0f;
		_isTargetingOtherTransform = false;
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
		if (_controlable)
		{

			float camSpeed = 10.0f / getEnvironment()->getFPS();

			if (!getCore()->getInput()->isJoystickConnected())
			{
				moveForward = getInput()->getKey(Input::FORWARD);
				moveBack = getCore()->getInput()->getKey(Input::BACK);
				moveLeft = getCore()->getInput()->getKey(Input::LEFT);
				moveRight = getCore()->getInput()->getKey(Input::RIGHT);

				if (moveForward && !lockUpMovement)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() += glm::normalize(glm::cross(glm::cross(camFront, camUp), camFront)) * camSpeed);
				}
				if (moveBack && !lockDownMovement)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() -= glm::normalize(glm::cross(glm::cross(camFront, camUp), camFront)) * camSpeed);
				}
				if (moveLeft)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed);
				}
				if (moveRight)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() += glm::normalize(glm::cross(camFront, camUp)) * camSpeed);
				}



				//float xoffset = getInput()->getMousePos().x - _lastx;
				//float yoffset = _lasty - getInput()->getMousePos().y;
				//_lastx = getInput()->getMousePos().x;
				//_lasty = getInput()->getMousePos().y;

				//xoffset *= _sensitivity;
				//yoffset *= _sensitivity;

				//_yaw += xoffset;
				//_pitch += yoffset;
			}
			else
			{
				moveForward = getInput()->GetJoystickAxis(Input::RIGHTSTICK).y < -8000;
				moveBack = getInput()->GetJoystickAxis(Input::RIGHTSTICK).y > 8000;
				moveLeft = getInput()->GetJoystickAxis(Input::RIGHTSTICK).x < -8000;
				moveRight = getInput()->GetJoystickAxis(Input::RIGHTSTICK).x > 8000;

				if (moveForward && !lockUpMovement)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() += glm::normalize(glm::cross(glm::cross(camFront, camUp), camFront)) * camSpeed);
				}
				if (moveBack && !lockDownMovement)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() -= glm::normalize(glm::cross(glm::cross(camFront, camUp), camFront)) * camSpeed);
				}
				if (moveLeft)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() -= glm::normalize(glm::cross(camFront, camUp)) * camSpeed);
				}
				if (moveRight)
				{
					getEntity()->getComponent<Transform>()->setPosition(getEntity()->getComponent<Transform>()->getPosition() += glm::normalize(glm::cross(camFront, camUp)) * camSpeed);
				}


				//float xoffset = 0;
				//if (getInput()->GetJoystickAxis(Input::RIGHTSTICK).x < -8000)
				//{
				//	xoffset = -_controllerRotationForce;
				//}
				//else if (getInput()->GetJoystickAxis(Input::RIGHTSTICK).x > 8000)
				//{
				//	xoffset = _controllerRotationForce;
				//}

				//float yoffset = 0;
				//if (getInput()->GetJoystickAxis(Input::RIGHTSTICK).y < -8000)
				//{
				//	yoffset = _controllerRotationForce;
				//}
				//else if (getInput()->GetJoystickAxis(Input::RIGHTSTICK).y > 8000)
				//{
				//	yoffset = -_controllerRotationForce;
				//}

				//xoffset *= _sensitivity;
				//yoffset *= _sensitivity;

				//_yaw += xoffset;
				//_pitch += yoffset;
			}

			if (_pitch > 89.0f)
			{
				_pitch = 89.0f;
			}
			if (_pitch < -89.0f)
			{
				_pitch = -89.0f;
			}

			if (getEntity()->getComponent<Transform>()->getPosition().y > 7.0f)
			{
				lockUpMovement = true;
			}
			else
			{
				lockUpMovement = false;
			}

			if (getEntity()->getComponent<Transform>()->getPosition().y < -7.0f)
			{
				lockDownMovement = true;
			}
			else
			{
				lockDownMovement = false;
			}

			glm::vec3 front;
			//front.x = cos(glm::radians(_pitch)) * cos(glm::radians(_yaw));
			//front.y = sin(glm::radians(_pitch));
			//front.z = cos(glm::radians(_pitch)) * sin(glm::radians(_yaw));
			front = target.lock()->getPosition() - getEntity()->getComponent<Transform>()->getPosition();
			camFront = glm::normalize(front);
		}
	}

	void Camera::setTarget(std::weak_ptr<Transform> _target)
	{
		target = _target;
		_isTargetingOtherTransform = true;
	}

}