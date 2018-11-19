#include <GL/glew.h>
#include <memory>
#include "Component.h"
#include "glm.hpp"

namespace myengine
{
	class Shader;
	class Texture;
		

	class TriangleRenderer : public Component
	{
	private:
		glm::fvec4 _color;
		GLuint _positionVBOID;
		GLuint _textureVBOID;
		GLuint _vaoID;
		std::shared_ptr<Shader> _shaderProgram;
		std::shared_ptr<Texture> _texture;

	public:
		TriangleRenderer();
		~TriangleRenderer();

		//Accessing base class variable
		//c#: base.function(parameter);
		//c++: classname::function(parameter);

		void OnInit(std::weak_ptr<Entity> _parent) override;
		void OnBegin() override;
		void OnTick() override;
		void OnDisplay() override;
		void AttachShaderProgram(std::shared_ptr<Shader> _newShaderProgram);
		std::shared_ptr<Shader> getShaderProgram();
		void AttachTexture(std::shared_ptr<Texture> _newTexture);
		std::shared_ptr<Texture> getTexture();

	};

}
