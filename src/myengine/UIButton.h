#include "Component.h"
#include "glm.hpp"

namespace myengine
{
	class UIImage;

	class UIButton : public Component
	{
	public:


		void OnInit(std::weak_ptr<Entity> _parent);
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<UIImage> _targetimg);
		void OnTick() override;

		void setTargetImage(std::weak_ptr<UIImage> _newImage);
		void setidleColor(glm::vec3 _newIdleColor);
		void setpressedColor(glm::vec3 _newPressedColor);

	private:
		std::weak_ptr<UIImage> _targetImage;
		glm::vec3 idleColor;
		glm::vec3 pressedColor;
		bool buttonPressed;
		bool isMouseOverlapping();

	};

}