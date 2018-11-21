#include "Collider.h"
#include "Core.h"
#include "Entity.h"
#include "Transform.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>
#include <gtc/matrix_transform.hpp>



namespace myengine
{
	void Collider::OnInit(std::weak_ptr<Entity> _parent, glm::vec3 boxscale)
	{
		Component::OnInit(_parent);
		_boxScale = boxscale;

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

		_numOfVertices = colliderVertices.size();

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * colliderVertices.size(), &colliderVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		_shaderProgram = getCore()->getHitboxShader();

		_drawWireframe = true;
		_colliding = false;
	}

	void Collider::OnTick()
	{
		Component::OnTick();
		_collidingEntities.clear();
		std::vector<std::weak_ptr<Entity>> EntitiesWithColliders = getCore()->getEntitiesWithComponent<Collider>();
		for (size_t i = 0; i < EntitiesWithColliders.size(); i++)
		{
			if (EntitiesWithColliders[i].lock()->getComponent<Collider>()->CheckIfColliding(getEntity()->getComponent<Transform>()->getPosition(), _boxScale))
			{
				_collidingEntities.push_back(EntitiesWithColliders[i]);
			}
		}
		
		if (_collidingEntities.size() > 1)
		{
			_colliding = true;
		}
		else
		{
			_colliding = false;
		}

		if (_drawWireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

			glUseProgram(_shaderProgram->getID());
			_shaderProgram->SetUniform("projection", getEntity()->getCore()->getMainCamera()->getProjectionMatrix());
			_shaderProgram->SetUniform("view", getEntity()->getCore()->getMainCamera()->getViewMatrix());

			glm::mat4 model = glm::mat4(1.0f), trans = glm::mat4(1.0f), sca = glm::mat4(1.0f);

			trans = glm::translate(trans, getEntity()->getComponent<Transform>()->getPosition());

			sca = glm::scale(sca, _boxScale);

			model = trans *  sca;

			_shaderProgram->SetUniform("model", model);

			if (!_colliding)
			{
				_shaderProgram->SetUniform("color", glm::vec3(1.0f, 0.0f, 0.0f));
			}
			else
			{
				_shaderProgram->SetUniform("color", glm::vec3(0.0f, 1.0f, 0.0f));
			}

			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, _numOfVertices);
			glBindVertexArray(0);
			glUseProgram(0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

	}

	bool Collider::CheckIfColliding(glm::vec3 _position, glm::vec3 _scale)
	{
		return (glm::abs(getEntity()->getComponent<Transform>()->getPosition().x - _position.x) < (_boxScale.x + _scale.x)) &&
			   (glm::abs(getEntity()->getComponent<Transform>()->getPosition().y - _position.y) < (_boxScale.y + _scale.y)) &&
			   (glm::abs(getEntity()->getComponent<Transform>()->getPosition().z - _position.z) < (_boxScale.z + _scale.z));
	}

	bool Collider::isColliding()
	{
		return _colliding;
	}
}