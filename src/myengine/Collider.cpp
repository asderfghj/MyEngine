#include "Collider.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>
#include <gtc/matrix_transform.hpp>



namespace frontier
{
	void Collider::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 boxscale)
	{
		Component::OnInit(_parent);
		Copyable = true;
		m_boxScale = boxscale;

		std::vector<GLfloat> colliderVertices = {
			// cube positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		m_numOfVertices = colliderVertices.size();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colliderVertices.size(), &colliderVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_shaderProgram = getCore()->getHitboxShader();

		m_drawWireframe = false;
		m_colliding = false;
	}

	void Collider::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<Collider> _original)
	{
		Component::OnInit(_parent);
		Copyable = true;
		m_boxScale = _original.lock()->GetBoxScale();

		std::vector<GLfloat> colliderVertices = {
			// cube positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		m_numOfVertices = colliderVertices.size();

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colliderVertices.size(), &colliderVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		m_shaderProgram = getCore()->getHitboxShader();

		m_drawWireframe = false;
		m_colliding = false;
	}

	void Collider::OnTick()
	{
		Component::OnTick();
		m_collidingEntities.clear();
		std::vector<std::weak_ptr<Entity>> EntitiesWithColliders = getCore()->getEntitiesWithComponent<Collider>();
		for (size_t i = 0; i < EntitiesWithColliders.size(); i++)
		{
			if (EntitiesWithColliders[i].lock()->getComponent<Collider>()->CheckIfColliding(getEntity()->getComponent<Transform>()->getPosition(), m_boxScale * getEntity()->getComponent<Transform>()->getScale()) && EntitiesWithColliders[i].lock()->isActive())
			{
				m_collidingEntities.push_back(EntitiesWithColliders[i]);
			}
		}
		
		if (m_collidingEntities.size() > 1)
		{
			m_colliding = true;
		}
		else
		{
			m_colliding = false;
		}

		if (m_drawWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glUseProgram(m_shaderProgram->getID());
			m_shaderProgram->SetUniform("projection", getEntity()->getCore()->getMainCamera()->GetProjectionMatrix());
			m_shaderProgram->SetUniform("view", getEntity()->getCore()->getMainCamera()->GetViewMatrix());

			glm::mat4 model = glm::mat4(1.0f), trans = glm::mat4(1.0f), sca = glm::mat4(1.0f);

			trans = glm::translate(trans, getEntity()->getComponent<Transform>()->getPosition());

			sca = glm::scale(sca, m_boxScale * getEntity()->getComponent<Transform>()->getScale());

			model = trans *  sca;

			m_shaderProgram->SetUniform("model", model);

			if (!m_colliding)
			{
				m_shaderProgram->SetUniform("color", glm::vec3(1.0f, 0.0f, 0.0f));
			}
			else
			{
				m_shaderProgram->SetUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
			}

			glBindVertexArray(m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, m_numOfVertices);
			glBindVertexArray(0);
			glUseProgram(0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	}

	bool Collider::CheckIfColliding(glm::vec3 _position, glm::vec3 _scale)
	{
		return (glm::abs(getEntity()->getComponent<Transform>()->getPosition().x - _position.x) < (m_boxScale.x * getEntity()->getComponent<Transform>()->getScale().x + _scale.x)) &&
			   (glm::abs(getEntity()->getComponent<Transform>()->getPosition().y - _position.y) < (m_boxScale.y * getEntity()->getComponent<Transform>()->getScale().y + _scale.y)) &&
			   (glm::abs(getEntity()->getComponent<Transform>()->getPosition().z - _position.z) < (m_boxScale.z * getEntity()->getComponent<Transform>()->getScale().z + _scale.z));
	}

	std::vector<std::weak_ptr<Entity>> Collider::GetCollidingEntities()
	{
		return m_collidingEntities;
	}

	bool Collider::IsColliding()
	{
		return m_colliding;
	}

	glm::vec3 Collider::GetBoxScale()
	{
		return m_boxScale;
	}
}