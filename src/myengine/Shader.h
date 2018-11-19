#ifndef SHADER_H_

#define SHADER_H_


#include "Resource.h"
#include "glm.hpp"
#include <GL/glew.h>
#include <memory>
#include <vector>

namespace myengine
{
	class Texture;
	class Resources;
	class CubemapTexture;

	class Shader : public Resource
	{
	private:
		GLuint _id;

	public:
		Shader();
		~Shader();
		static std::shared_ptr<Shader> Create(std::string _fragScr, std::string _vertScr, std::vector<GLchar*> _attributes, std::shared_ptr<Resources> _resources);
		void SetUniform(const GLchar *_name, float _value, bool _unsetProgram = false);
		void SetUniform(const GLchar *_name, int _value, bool _unsetProgram = false);
		void SetUniform(const GLchar *_name, std::weak_ptr<Texture> _texture, bool _unsetProgram = false);
		void SetUniform(const GLchar *_name, std::weak_ptr<CubemapTexture> _texture, bool _unsetprogram = false);
		void SetUniform(const GLchar *_name, glm::mat4 _value, bool _unsetProgram = false, bool _transpose = false);
		void SetUniform(const GLchar *_name, glm::vec3 _value, bool _unsetProgram = false);
		void SetUniform(const GLchar *_name, std::vector<std::weak_ptr<Texture>> _values, bool _unsetProgram = false);

		void setID(GLuint _newID);
		GLuint getID();

	};

}

#endif // !SHADER_H_