#include "TriangleRenderer.h"
#include <iostream>

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

	_vboID = 0;

	glGenBuffers(1, &_vboID);

	if (!_vboID)
	{
		throw std::exception();
	}

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//VAO initialisation

	_vaoID = 0;

	glGenVertexArrays(1, &_vaoID);

	if (!_vaoID)
	{
		throw std::exception();
	}

	glBindVertexArray(_vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, _vboID);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Vertex Shader
	GLint ShaderSuccess = 0;

	const GLchar *vertexShaderSrc =
		"attribute vec3 in_Position;				"\
		"											"\
		"void main()								"\
		"{											"\
		"	gl_Position = vec4(in_Position, 1.0);	"\
		"}											";

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderID);
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &ShaderSuccess);

	if (!ShaderSuccess)
	{
		throw std::exception();
	}

	//Fragment Shader
	const GLchar *fragmentShaderSrc =
		"void main()							"\
		"{										"\
		"	gl_FragColor = vec4(0, 0, 1, 1);	"\
		"}										";

	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderSrc, NULL);
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &ShaderSuccess);

	if (!ShaderSuccess)
	{
		throw std::exception();
	}

	//program creation

	_programID = glCreateProgram();
	glAttachShader(_programID, vertexShaderID);
	glAttachShader(_programID, fragmentShaderID);

	glBindAttribLocation(_programID, 0, "in_position");

	glLinkProgram(_programID);
	glGetProgramiv(_programID, GL_LINK_STATUS, &ShaderSuccess);

	if (!ShaderSuccess)
	{
		throw std::exception();
	}

	glDetachShader(_programID, vertexShaderID);
	glDeleteShader(vertexShaderID);
	glDetachShader(_programID, fragmentShaderID);
	glDeleteShader(fragmentShaderID);

	if (!ShaderSuccess)
	{
		throw std::exception();
	}

}

void TriangleRenderer::OnBegin()
{
	Component::OnBegin();
}

void TriangleRenderer::OnTick()
{
	Component::OnTick();
	glUseProgram(_programID);
	//int vertexColorLocation = glGetUniformLocation(_programID, "uni_color");
	//glUniform4f(vertexColorLocation, _color.x, _color.y, _color.z, _color.w);
	glBindVertexArray(_vaoID);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
	glUseProgram(0);
}

void TriangleRenderer::OnDisplay()
{
	Component::OnDisplay();
}

void TriangleRenderer::SetColor(glm::fvec4 _newColor)
{
	std::cout << "Color Changed" << std::endl;
	_color = _newColor;
}
