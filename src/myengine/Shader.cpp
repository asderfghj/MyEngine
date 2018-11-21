#include "Shader.h"
#include "Resources.h"
#include "Texture.h"
#include "CubemapTexture.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "gtc/type_ptr.hpp"


namespace frontier
{

	Shader::Shader()
	{
		std::cout << "Shader Created" << std::endl;
	}

	Shader::~Shader()
	{
		std::cout << "Shader Destroyed" << std::endl;
	}

	std::shared_ptr<Shader> Shader::Create(std::string _fragScr, std::string _vertScr, std::vector<GLchar*> _attributes, std::shared_ptr<Resources> _resources)
	{
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		std::shared_ptr<Shader> rtn = std::make_shared<Shader>();

		vShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit || std::ifstream::badbit);

		try
		{
			vShaderFile.open(_vertScr);
			fShaderFile.open(_fragScr);
			std::stringstream vShaderStream, fShaderStream;

			vShaderStream << vShaderFile.rdbuf();

			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();

		}
		catch(std::ifstream::failure e)
		{
			std::cout << "Shader file not read" << std::endl;
		}

		GLint ShaderSuccess = 0;

		const GLchar* vShaderCode = vertexCode.c_str();
		const GLchar* fShaderCode = fragmentCode.c_str();


		GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShaderID, 1, &vShaderCode, NULL);
		glCompileShader(vertexShaderID);
		glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &ShaderSuccess);

		if (!ShaderSuccess)
		{
			throw std::exception();
		}

		GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShaderID, 1, &fShaderCode, NULL);
		glCompileShader(fragmentShaderID);
		glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &ShaderSuccess);

		if (!ShaderSuccess)
		{
			throw std::exception();
		}

		GLuint ProgramId = glCreateProgram();

		glAttachShader(ProgramId, vertexShaderID);
		glAttachShader(ProgramId, fragmentShaderID);

		for (size_t i = 0; i < _attributes.size(); i++)
		{
			glBindAttribLocation(ProgramId, i, _attributes[i]);
		}

		glLinkProgram(ProgramId);
		glGetProgramiv(ProgramId, GL_LINK_STATUS, &ShaderSuccess);


		if (!ShaderSuccess)
		{
			throw std::exception();
		}

		glDetachShader(ProgramId, vertexShaderID);
		glDeleteShader(vertexShaderID);
		glDetachShader(ProgramId, fragmentShaderID);
		glDeleteShader(fragmentShaderID);

		rtn->setID(ProgramId);

		_resources->AddCreatedResource(rtn);

		return rtn;

	}

	void Shader::SetUniform(const GLchar* _name, float _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniform1f(UniformLocation, _value);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, int _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniform1i(UniformLocation, _value);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, std::weak_ptr<Texture> _texture, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniform1i(UniformLocation, _texture.lock()->GetTextureLocation());
	}

	void Shader::SetUniform(const GLchar* _name, std::weak_ptr<CubemapTexture> _texture, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniform1i(UniformLocation, _texture.lock()->GetTextureLocation());
	}

	void Shader::SetUniform(const GLchar* _name, glm::mat4 _value, bool _transpose, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniformMatrix4fv(UniformLocation, 1, _transpose, glm::value_ptr(_value));
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, glm::vec3 _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniform3fv(UniformLocation, 1, &_value[0]);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, glm::vec4 _value, bool _unsetProgram)
	{
		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniform4fv(UniformLocation, 1, &_value[0]);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::SetUniform(const GLchar* _name, std::vector<std::weak_ptr<Texture>> _values, bool _unsetProgram)
	{
		std::vector<int> _ids;

		for (size_t i = 0; i < _values.size(); i++)
		{
			_ids.push_back(_values.at(i).lock()->GetTextureLocation());
		}

		GLint UniformLocation = glGetUniformLocation(_id, _name);
		glUseProgram(_id);
		glUniform1iv(UniformLocation, _values.size(), &_ids[0]);
		if (_unsetProgram)
		{
			glUseProgram(0);
		}
	}

	void Shader::setID(GLuint _newID)
	{
		_id = _newID;
	}

	GLuint Shader::getID()
	{
		return _id;
	}

}