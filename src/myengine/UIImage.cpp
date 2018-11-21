#include "UIImage.h"
#include "Entity.h"
#include "Core.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Transform.h"

namespace frontier
{
	void UIImage::OnInit(std::weak_ptr<Entity> _parent)
	{
		Component::OnInit(_parent);
		_shader = _parent.lock()->getCore()->getUntexturedUiImageShader();
		_preserveAspect = false;
		_customShader = false;
		_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		InitialiseQuad();
	}

	void UIImage::OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Texture> _newtexture, bool preserveAspect)
	{
		Component::OnInit(_parent);
		_shader = _parent.lock()->getCore()->getTexturedUiImageShader();
		_preserveAspect = preserveAspect;
		_customShader = false;
		_texture = _newtexture;
		_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		InitialiseQuad();
	}

	void UIImage::OnTick()
	{
		if (_texture)
		{
			_shader->SetUniform("texture", _texture);
			_texture->BindTexture();
		}

		glUseProgram(_shader->getID());

		_shader->SetUniform("ortho", getCore()->getMainCamera()->getOrthographicMatrix());
		if (_preserveAspect)
		{
			_shader->SetUniform("model", getEntity()->getComponent<Transform>()->getModelMatrixModScale(glm::vec3(_texture->getWidth(), _texture->getHeight(), 1.0f)));
		}
		else
		{
			_shader->SetUniform("model", getEntity()->getComponent<Transform>()->getModelMatrix());
		}
		_shader->SetUniform("color", _color);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, verticesCount / 3);
		glBindVertexArray(0);
		glUseProgram(0);

	}

	void UIImage::AttachShader(std::shared_ptr<Shader> _newShader)
	{
		_shader = _newShader;
		_customShader = true;
	}

	void UIImage::AttachTexture(std::shared_ptr<Texture> _newTexture, bool preserveAspect)
	{
		_texture = _newTexture;
		_preserveAspect = preserveAspect;
		if (!_customShader)
		{
			if (_texture)
			{
				_shader = getEntity()->getCore()->getTexturedUiImageShader();
			}
			else
			{
				_shader = getEntity()->getCore()->getUntexturedUiImageShader();
			}
		}
	}

	void UIImage::setColor(glm::vec4 _newColor)
	{
		_color = _newColor;
	}

	void UIImage::InitialiseQuad()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &posVBO);
		glGenBuffers(1, &texVBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, posVBO);

		std::vector<GLfloat> verts = {
			-1.0f,  1.0f,  0.0f,
			 1.0f,  1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f,

			 1.0f, -1.0f,  0.0f,
			-1.0f, -1.0f,  0.0f,
			-1.0f,  1.0f,  0.0f
		};

		verticesCount = verts.size();

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * verts.size(), &verts.at(0), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

		if (_texture)
		{
			glBindBuffer(GL_ARRAY_BUFFER, texVBO);

			std::vector<GLfloat> texcoords = {
				0.0f, 1.0f,
				1.0f, 1.0f,
				1.0f, 0.0f,

				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f
			};

			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * texcoords.size(), &texcoords.at(0), GL_STATIC_DRAW);

			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (void*)0);
		}


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

	}
}