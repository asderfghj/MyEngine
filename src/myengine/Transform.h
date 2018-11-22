#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "glm.hpp"
#include "Component.h"
#include <vector>
#include <memory>

namespace frontier
{
	class Entity;

	class Transform: public Component
	{
	private:
		glm::vec3 _position;
		glm::vec3 _rotation;
		glm::vec3 _scale;
		std::vector<std::weak_ptr<Transform>> _children;
		std::weak_ptr<Transform> _transformParent;
		bool _isChildOfOtherTransform;
		std::weak_ptr<Transform> _self;
	public:
		using Component::OnInit;
		void OnInit(std::weak_ptr<Entity> parent) override;
		void OnInit(std::weak_ptr<Entity> parent, glm::vec3 position);
		void OnInit(std::weak_ptr<Entity> parent, glm::vec3 position, glm::vec3 rotation);
		void OnInit(std::weak_ptr<Entity> parent, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

		glm::vec3 getPosition();
		void setPosition(glm::vec3 _pos);
		glm::vec3 getRotation();
		void setRotation(glm::vec3 _rot);
		glm::vec3 getScale();
		void setScale(glm::vec3 _sca);
		glm::mat4 getModelMatrix(bool applyRotationAfterTranslation = false);
		glm::mat4 getModelMatrixModScale(glm::vec3 scaleModifier);
		glm::mat4 getPositionMatrix(int excludeAxis = 0);
		void setTransformParent(std::weak_ptr<Transform> _parent);
		void addChild(std::weak_ptr<Transform> _child);
		void setSelf(std::weak_ptr<Transform> self);
	};
}

#endif // !TRANSFORM_H_