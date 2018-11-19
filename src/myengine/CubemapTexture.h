#include "Resource.h"
#include <memory>
#include <string>
#include <vector>
#include <GL/glew.h>

namespace myengine
{
	class Resources;

	class CubemapTexture : public Resource
	{
	public:
		static std::shared_ptr<CubemapTexture> Create(std::vector<std::string> _paths, std::shared_ptr<Resources> _resources, int _TextureLocation);
		void SetTexture(GLuint _newID, int _TextureLocation);
		GLuint GetTexture();
		int GetTextureLocation();
		void Bindtexture();
	private:
		GLuint _id;
		int _textureLocation;
	};
}