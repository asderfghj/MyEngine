#include "TriangleRenderer.h"

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
		"out vec4 FragColor							"\
		"											"\
		"uniform vec4 uni_color						"\
		"											"\
		"void main()								"\
		"{											"\
		"	gl_Position = vec4(in_Position, 1.0);	"\
		"											"\
		"	out_color = uni_color					"\
		"}											";

	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderId, 1, &vertexShaderSrc, NULL);
	glCompileShader(vertexShaderId);
	glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &ShaderSuccess);

	if (!ShaderSuccess)
	{
		throw std::exception();
	}

	//Fragment Shader
	const GLchar *fragmentShaderSrc =
		"										"\
		"in vec4 FragColor						"\
		"										"\
		"void main()							"\
		"{										"\
		"	gl_FragColor = FragColor;			"\
		"}										";



}
