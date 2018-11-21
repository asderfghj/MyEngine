#include "Component.h"
#include "glm.hpp"
#include <GL/glew.h>

namespace frontier
{
	class Texture;
	class Shader;

	class UIImage : public Component
	{
	public:
		void OnInit(std::weak_ptr<Entity> _parent);
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Texture> _newtexture, bool preserveAspect = false);
		void OnTick() override;
		void AttachShader(std::shared_ptr<Shader> _newShader);
		void AttachTexture(std::shared_ptr<Texture> _newTexture, bool preserveAspect = false);
		void setColor(glm::vec4 _newColor);

	private:
		void InitialiseQuad();
		std::shared_ptr<Shader> _shader;
		std::shared_ptr<Texture> _texture;
		glm::vec4 _color;
		GLuint VAO, posVBO, texVBO, verticesCount;
		bool _preserveAspect, _customShader;

	};
}