#include "Mesh.h"
#include "Model.h"
#include "Transform.h"
#include "Entity.h"
#include "Core.h"
#include "Camera.h"
#include "Texture.h"
#include <GL/glew.h>

namespace myengine
{
	Mesh::Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals, std::vector<GLfloat> _texcoords)
	{
		vertices = _vertices;
		normals = _normals;
		texCoords = _texcoords;
		setupMesh();
	}

	void Mesh::setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &vertVBO);
		glGenBuffers(1, &normVBO);
		glGenBuffers(1, &texCoordVBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, vertVBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices.size(), &vertices.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, normVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * normals.size(), &normals.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texCoords.size(), &texCoords.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void Mesh::Draw(glm::mat4 _model, glm::mat4 _view, glm::mat4 _proj, std::shared_ptr<Texture> _tex, std::shared_ptr<Shader> _shader)
	{
		if (_tex)
		{
			_shader->SetUniform("texture1", _tex);
			_tex->BindTexture();
		}

		glUseProgram(_shader->getID());

		_shader->SetUniform("model", _model);
		_shader->SetUniform("view", _view);
		_shader->SetUniform("projection", _proj);

		

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size());
		glBindVertexArray(0);
		glUseProgram(0);

	}
}