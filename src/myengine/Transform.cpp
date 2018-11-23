#include "Transform.h"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


namespace frontier
{
	void Transform::OnInit(std::weak_ptr<Entity> parent)
	{
		Component::OnInit(parent);
		_position = glm::vec3(0.0f, 0.0f, 0.0f);
		_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		_isChildOfOtherTransform = false;
	}

	void Transform::OnInit(std::weak_ptr<Entity> parent, glm::vec3 position)
	{
		Component::OnInit(parent);
		_position = position;
		_rotation = glm::vec3(0.0f, 0.0f, 0.0f);
		_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		_isChildOfOtherTransform = false;
	}

	void Transform::OnInit(std::weak_ptr<Entity> parent, glm::vec3 position, glm::vec3 rotation)
	{
		Component::OnInit(parent);
		_position = position;
		_rotation = rotation;
		_scale = glm::vec3(1.0f, 1.0f, 1.0f);
		_isChildOfOtherTransform = false;
	}


	void Transform::OnInit(std::weak_ptr<Entity> parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
	{
		Component::OnInit(parent);
		_position = position;
		_rotation = rotation;
		_scale = scale;
		_isChildOfOtherTransform = false;
	}


	glm::vec3 Transform::getPosition()
	{
		return _position;
	}

	void Transform::setPosition(glm::vec3 _pos)
	{
		_position = _pos;
	}

	glm::vec3 Transform::getRotation()
	{
		return _rotation;
	}

	void Transform::setRotation(glm::vec3 _rot)
	{
		_rotation = _rot;
	}

	glm::vec3 Transform::getScale()
	{
		return _scale;
	}

	void Transform::setScale(glm::vec3 _sca)
	{
		_scale = _sca;
	}

	glm::mat4 Transform::getModelMatrix(bool applyRotationAfterTranslation)
	{
		glm::mat4 rtn = glm::mat4(1.0f), trans = glm::mat4(1.0f), rotx = glm::mat4(1.0f), roty = glm::mat4(1.0f), rotz = glm::mat4(1.0f), sca = glm::mat4(1.0f);
		trans = glm::translate(trans, _position);
		sca = glm::scale(sca, _scale);
		rotx = glm::rotate(rotx, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		roty = glm::rotate(roty, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotz = glm::rotate(rotz, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		if (!applyRotationAfterTranslation)
		{
			rtn = trans * rotz * rotx * roty * sca;
		}

		else
		{
			rtn =  rotz * rotx * roty * trans * sca;
		}

		if(_isChildOfOtherTransform)
		{
			rtn = rtn * _transformParent.lock()->getModelMatrix();
		}

		return rtn;
	}

	glm::mat4 Transform::getModelMatrixModScale(glm::vec3 scaleModifier)
	{
		glm::vec3 modifiedScale = scaleModifier * _scale;

		glm::mat4 rtn = glm::mat4(1.0f), trans = glm::mat4(1.0f), rotx = glm::mat4(1.0f), roty = glm::mat4(1.0f), rotz = glm::mat4(1.0f), sca = glm::mat4(1.0f);
		trans = glm::translate(trans, _position);
		sca = glm::scale(sca, modifiedScale);
		rotx = glm::rotate(rotx, glm::radians(_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		roty = glm::rotate(roty, glm::radians(_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotz = glm::rotate(rotz, glm::radians(_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

		rtn = trans * rotz * rotx * roty * sca;

		if (_isChildOfOtherTransform)
		{
			rtn = rtn * _transformParent.lock()->getModelMatrix();
		}

		return rtn;
	}

	glm::mat4 Transform::getPositionMatrix(int excludeaxis)
	{
		glm::mat4 rtn;
		if (excludeaxis == 1)
		{
			rtn = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, _position.y, _position.z));
		}
		else if (excludeaxis == 2)
		{
			rtn = glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, 0.0f, _position.z));
		}
		else if (excludeaxis == 3)
		{
			rtn = glm::translate(glm::mat4(1.0f), glm::vec3(_position.x, _position.y, 0.0f));
		}
		else
		{
			rtn = glm::translate(glm::mat4(1.0f), _position);
		}
		return rtn;
	}

	void Transform::setTransformParent(std::weak_ptr<Transform> _parent)
	{
		_transformParent = _parent;
		_isChildOfOtherTransform = true;
	}

	void Transform::addChild(std::weak_ptr<Transform> _child)
	{
		_children.push_back(_child);
		_child.lock()->setTransformParent(_self);
	}

	void Transform::setSelf(std::weak_ptr<Transform> self)
	{
		_self = self;
	}
}