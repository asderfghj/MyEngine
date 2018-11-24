#ifndef COLLIDER_H_
#define COLLIDER_H_

#include <GL/glew.h>
#include <vector>
#include "glm.hpp"
#include "Component.h"

namespace frontier
{
	class Shader;

	class Collider : public Component
	{
	private:
		glm::vec3 m_boxScale;
		int m_numOfVertices;
		bool m_colliding, m_drawWireframe;
		std::vector<std::weak_ptr<Entity>> m_collidingEntities;
		GLuint m_VAO, m_VBO;
		std::shared_ptr<Shader> m_shaderProgram;

	public:
		//!
		void OnInit(std::weak_ptr<Entity> _parent, glm::vec3 _boxScale = glm::vec3(1.0f,1.0f,1.0f));
		void OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Collider> _original);
		void OnTick() override;
		bool CheckIfColliding(glm::vec3 _position, glm::vec3 _scale);
		std::vector<std::weak_ptr<Entity>> GetCollidingEntities();
		bool IsColliding();
		glm::vec3 GetBoxScale();

	};

}

#endif