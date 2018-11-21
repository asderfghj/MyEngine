#include "Component.h"
#include <memory>
#include <vector>
#include <GL/glew.h>

namespace frontier
{
	class Entity;
	class CubemapTexture;
	class Shader;

	class Skybox : public Component 
	{
	public:
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<CubemapTexture> _skyboxTexture);
		void OnTick() override;

	private:
		std::shared_ptr<CubemapTexture> _texture;
		std::shared_ptr<Shader> _shaderProgram;
		GLuint VBO, VAO;
		std::vector<GLfloat> skyboxVertices;
	};


}