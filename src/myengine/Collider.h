#include "Component.h"
#include "glm.hpp"
#include <GL/glew.h>
#include <vector>

namespace myengine
{
	class Shader;

	class Collider : public Component
	{
	public:
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 boxscale = glm::vec3(1.0f,1.0f,1.0f));
		void OnTick() override;
		bool CheckIfColliding(glm::vec3 _position, glm::vec3 _scale);
		bool isColliding();
	private:
		glm::vec3 _boxScale;
		int _numOfVertices;
		bool _colliding, _drawWireframe;
		std::vector<std::weak_ptr<Entity>> _collidingEntities;
		GLuint VAO, VBO;
		std::shared_ptr<Shader> _shaderProgram;
	};

}