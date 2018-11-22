#include "glm.hpp"
#include "Shader.h"
#include <string>
#include <vector>
#include <memory>
#include <glm.hpp>
#include <GL/glew.h>

namespace frontier
{
	class Model;
	class Texture;

	class Mesh 
	{
	public:
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> normals;
		std::vector<GLfloat> texCoords;

		Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals, std::vector<GLfloat> _texcoords);
		Mesh(std::vector<GLfloat> _vertices, std::vector<GLfloat> _normals);
		void Draw(glm::mat4 _model, glm::mat4 _view, glm::mat4 _proj, std::shared_ptr<Texture> _tex, std::shared_ptr<Shader> _shader);

	private:
		unsigned int VAO, vertVBO, normVBO, texCoordVBO;
		void setupMesh();
		void setupMeshNoTexCoords();
	};





}