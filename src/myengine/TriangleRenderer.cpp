#include "TriangleRenderer.h"
#include "Shader.h"
#include "Texture.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"
#include <iostream>

namespace myengine
{

	TriangleRenderer::TriangleRenderer()
	{
	}


	TriangleRenderer::~TriangleRenderer()
	{
		std::cout << "Triangle Renderer Destroyed" << std::endl;
	}


	void TriangleRenderer::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);

		//VBO initialisation
		const GLfloat positions[] = {
			0.0f, 0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f

		};

		_positionVBOID = 0;

		glGenBuffers(1, &_positionVBOID);

		if (!_positionVBOID)
		{
			throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, _positionVBOID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		const GLfloat textureCoords[] =
		{
			0.5f, 1.0f,
			0.0f, 0.0f,
			1.0f, 0.0f
		};

		_textureVBOID = 0;

		glGenBuffers(1, &_textureVBOID);

		if (!_textureVBOID)
		{
			throw std::exception();
		}

		glBindBuffer(GL_ARRAY_BUFFER, _textureVBOID);

		glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), textureCoords, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		//VAO initialisation

		_vaoID = 0;

		glGenVertexArrays(1, &_vaoID);

		if (!_vaoID)
		{
			throw std::exception();
		}

		glBindVertexArray(_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, _positionVBOID);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, _textureVBOID);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);

		glEnableVertexAttribArray(2);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);


	}

	void TriangleRenderer::OnBegin()
	{
		Component::OnBegin();
	}

	void TriangleRenderer::OnTick()
	{
		Component::OnTick();
		//glUseProgram(_programID);
		glUseProgram(_shaderProgram->getID());
		if (_texture)
		{
			_shaderProgram->SetUniform("texture1", _texture);
		}

		_shaderProgram->SetUniform("model", getEntity()->getComponent<Transform>()->getModelMatrix());
		_shaderProgram->SetUniform("view", getCore()->getMainCamera()->getViewMatrix());
		_shaderProgram->SetUniform("projection", getCore()->getMainCamera()->getOrthographicMatrix());

		if (_texture)
		{
			_texture->BindTexture();
		}

		glBindVertexArray(_vaoID);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		glUseProgram(0);
	}

	void TriangleRenderer::OnDisplay()
	{
		Component::OnDisplay();
	}

	void TriangleRenderer::AttachShaderProgram(std::shared_ptr<Shader> _newShaderProgram)
	{
		_shaderProgram = _newShaderProgram;
	}

	std::shared_ptr<Shader> TriangleRenderer::getShaderProgram()
	{
		return _shaderProgram;
	}

	void TriangleRenderer::AttachTexture(std::shared_ptr<Texture> _newTexture)
	{
		_texture = _newTexture;
	}

	std::shared_ptr<Texture> TriangleRenderer::getTexture()
	{
		return _texture;
	}

}