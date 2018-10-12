#include <GL/glew.h>
#include <memory>
#include "Component.h"
#include "glm.hpp"

class Entity;

class TriangleRenderer : Component
{
private:
	glm::uvec4 _color;
	GLuint _vboID;
	GLuint _vaoID;
	GLuint _programID;

public:
	TriangleRenderer();
	~TriangleRenderer();

	//REMINDER OF HOW BAD I AM WITH C++
	//Accessing base class variable
	//c#: base.function(parameter);
	//c++: classname::function(parameter);

	void OnInit(std::weak_ptr<Entity> _parent) override;
	void OnBegin() override;
	void OnTick() override;
	void OnDisplay() override;
	void SetColor(glm::uvec4 _newColor);

};
