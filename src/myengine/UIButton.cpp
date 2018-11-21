#include "UIButton.h"
#include "UIImage.h"
#include "Input.h"
#include "Entity.h"
#include "Transform.h"
#include <iostream>

namespace frontier
{

	void UIButton::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		if (_parent.lock()->hasComponent<UIImage>())
		{
			_targetImage = _parent.lock()->getComponent<UIImage>();
			
		}
	}

	void UIButton::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<UIImage> _targetimg)
	{
		Component::OnInit(_parent);
		_targetImage = _targetimg;
	}

	void UIButton::OnTick()
	{
		if (isMouseOverlapping() && getInput()->getMouseButton(Input::LEFT_MOUSE_BUTTON))
		{
			std::cout << "Button Clicked" << std::endl;
			if (!_targetImage.expired())
			{
				_targetImage.lock()->setColor(glm::vec4(pressedColor, 1.0f));
			}
		}
		else if (isMouseOverlapping())
		{
			if (!_targetImage.expired())
			{
				_targetImage.lock()->setColor(glm::vec4(overlapColor, 1.0f));
			}
		}
		else
		{
			if (!_targetImage.expired())
			{
				_targetImage.lock()->setColor(glm::vec4(idleColor, 1.0f));
			}
		}
	}

	void UIButton::setTargetImage(std::weak_ptr<UIImage> _newImage)
	{
		_targetImage = _newImage;
	}

	void UIButton::setidleColor(glm::vec3 _newIdleColor)
	{
		idleColor = _newIdleColor;
	}

	void UIButton::setpressedColor(glm::vec3 _newPressedColor)
	{
		pressedColor = _newPressedColor;
	}

	void UIButton::setOverlapColor(glm::vec3 _newOverlapColor)
	{
		overlapColor = _newOverlapColor;
	}

	bool UIButton::isMouseOverlapping()
	{
		return (glm::abs(getEntity()->getComponent<Transform>()->getPosition().x - getInput()->getMousePos().x) < getEntity()->getComponent<Transform>()->getScale().x) &&
			(glm::abs(getEntity()->getComponent<Transform>()->getPosition().y - getInput()->getMousePos().y) < getEntity()->getComponent<Transform>()->getScale().y);
	}

}