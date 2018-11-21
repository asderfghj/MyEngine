#include "Resource.h"
#include <memory>
#include <string>
#include <GL/glew.h>

namespace frontier
{
	class Resources;

	class Texture : public Resource
	{
	public:
		static std::shared_ptr<Texture> Create(const char* _path, std::shared_ptr<Resources> _resources, int _TextureLocation);
		void SetTexture(GLuint _newID, int _TextureLocation);
		GLuint GetTexture();
		int GetTextureLocation();
		void BindTexture();
		void setWidth(int _newWidth);
		void setheight(int _newHeight);
		int getWidth();
		int getHeight();
	private:
		GLuint _id;
		int _textureLocation;
		int _width;
		int _height;
	};

}