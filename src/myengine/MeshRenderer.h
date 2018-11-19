#ifndef MESHRENDERER_H_
#define MESHRENDERER_H_

#include <GL/glew.h>
#include <memory>
#include <vector>
#include "Component.h"
#include "glm.hpp"

namespace myengine
{

	class Texture;
	class Shader;
	class Model;

	class MeshRenderer : public Component
	{
	private:
		std::shared_ptr<Model> _meshData;
		std::shared_ptr<Texture> _texture;
		std::shared_ptr<Shader> _shaderProgram;

	public:
		void OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Model> meshData);
		void OnTick() override;
		void AttachShaderProgram(std::shared_ptr<Shader> _newShaderProgram);
		void AttachTexture(std::shared_ptr<Texture> _newTexture);
	};
}

#endif // !MESHRENDERER_H_