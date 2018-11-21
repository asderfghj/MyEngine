#include "Component.h"
#include "glm.hpp"

namespace frontier
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
		void setOverlapColor(glm::vec3 _newOverlapColor);

	private:
		std::weak_ptr<UIImage> _targetImage;
		glm::vec3 idleColor;
		glm::vec3 pressedColor;
		glm::vec3 overlapColor;
		bool buttonPressed;
		bool isMouseOverlapping();

	};

}