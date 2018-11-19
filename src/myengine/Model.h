

#include "Shader.h"
#include "Component.h"
#include "Resource.h"
#include "Resources.h"
#include <vector>
#include <string>




namespace myengine
{

	class Mesh;
	class Texture;

	class Model : public Resource
	{
	friend class Mesh;
	public:
		Model();
		static std::shared_ptr<Model> Create(const char *path, std::weak_ptr<Resources> _resources);
		void Draw(glm::mat4 _model, glm::mat4 _view, glm::mat4 _proj, std::shared_ptr<Texture> _tex, std::shared_ptr<Shader> _shader);

	private:
		std::vector<std::shared_ptr<Mesh>> meshes;
		void loadModel(std::string path);


	};
}