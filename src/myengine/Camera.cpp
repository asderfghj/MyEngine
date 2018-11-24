#include <SDL2/SDL_keycode.h>
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include "Camera.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Input.h"
#include "Environment.h"
#include "Timer.h"


namespace frontier
{
	glm::mat4 Camera::GetViewMatrix()
	{
		glm::mat4 view;

		view = glm::inverse(GetEntity()->getComponent<Transform>()->GetModelMatrix());

		return view;
	}

	glm::mat4 Camera::GetProjectionMatrix()
	{
		glm::mat4 proj = glm::perspective(glm::radians(m_FOV), (float)GetCore()->GetWidth() / (float)GetCore()->GetHeight(), m_near, m_far);
		return proj;
	}

	glm::mat4 Camera::GetOrthographicMatrix()
	{
		glm::mat4 orth = glm::ortho(0.0f, (float)GetCore()->GetWidth(), 0.0f, (float)GetCore()->GetHeight(), m_near, m_far);
		return orth;
	}

	void Camera::OnInit(std::weak_ptr<Entity> _parent, float _fov, float _near, float _far)
	{
		Component::OnInit(_parent);
		m_FOV = _fov;
		m_near = _near;
		m_far = _far;
	}

	bool Camera::IsMainCamera()
	{
		return m_isMainCamera;
	}

	void Camera::SetIsMainCamera(bool _main)
	{
		m_isMainCamera = _main;
	}

}