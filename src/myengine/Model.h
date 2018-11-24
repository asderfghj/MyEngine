#include <vector>
#include <string>

#include "Shader.h"
#include "Component.h"
#include "Resource.h"
#include "Resources.h"

namespace frontier
{

	class Mesh;
	class Texture;

	//!A group of meshes that make up a model.
	class Model : public Resource
	{
	friend class Mesh;
	private:
		std::vector<std::shared_ptr<Mesh>> m_meshes;
		void LoadModel(std::string _path);
	public:
		//!Creates a model froma filepath to be used in a MeshRenderer.
		/*!
			\param _path The filepath for the model.
			\param _resources The resources class located in core.
		*/
		static std::shared_ptr<Model> Create(const char *_path, std::weak_ptr<Resources> _resources);

		//!Draws the model.
		/*!
			\param _model The model matrix.
			\param _view The view matrix, taken from the camera.
			\param _proj The projection matrix, taken from the camera.
			\param _tex The texture for the model.
			\param _shader The shader for the model.
		*/
		void Draw(glm::mat4 _model, glm::mat4 _view, glm::mat4 _proj, std::shared_ptr<Texture> _tex, std::shared_ptr<Shader> _shader);
	};
}