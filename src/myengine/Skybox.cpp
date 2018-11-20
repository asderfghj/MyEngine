#include "Skybox.h"
#include "Shader.h"
#include "Entity.h"
#include "Core.h"
#include "CubemapTexture.h"
#include "Camera.h"
#include <gtc/matrix_transform.hpp>

namespace myengine
{
	void Skybox::OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<CubemapTexture> _skyboxTexture)
	{
		Component::OnInit(_parent);
		_texture = _skyboxTexture;

		skyboxVertices = {
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

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * skyboxVertices.size(), &skyboxVertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		_shaderProgram = Shader::Create("../resources/fragmentshaders/skybox.fs", "../resources/vertexshaders/skybox.vs", { "in_position" }, _parent.lock()->getCore()->getResources());

	}

	void Skybox::OnTick()
	{
		Component::OnTick();
		
		glDepthMask(false);
		_shaderProgram->SetUniform("skybox", _texture);
		_texture->Bindtexture();
		
		glUseProgram(_shaderProgram->getID());

		_shaderProgram->SetUniform("projection", getEntity()->getCore()->getMainCamera()->getProjectionMatrix());
		_shaderProgram->SetUniform("view", glm::mat4(glm::mat3(getEntity()->getCore()->getMainCamera()->getViewMatrix())));
		glm::mat4 scaler = glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, 50.0f));
		


		_shaderProgram->SetUniform("scaler", scaler);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, skyboxVertices.size());
		glBindVertexArray(0);
		glUseProgram(0);
		glDepthMask(true);

	}

}