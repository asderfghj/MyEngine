#include <iostream>
#include "Texture.h"
#include "Resources.h"
#define STB_IMAGE_IMPLEMENTATION  
#include "stb_image.h"


namespace myengine
{
	std::shared_ptr<Texture> Texture::Create(const char* _path, std::shared_ptr<Resources> _resources, int _TextureLocation)
	{
		std::shared_ptr<Texture> rtn = std::make_shared<Texture>();
		GLuint rtnID;
		glActiveTexture(GL_TEXTURE0 + _TextureLocation);
		glGenTextures(1, &rtnID);
		glBindTexture(GL_TEXTURE_2D, rtnID);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char *data = stbi_load(_path, &width, &height, &nrChannels, 4);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
			throw std::exception();
		}
		rtn->setWidth(width);
		rtn->setheight(height);
		stbi_image_free(data);


		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);

		rtn->SetTexture(rtnID, _TextureLocation);
		_resources->AddCreatedResource(rtn);
		return rtn;
	}

	void Texture::SetTexture(GLuint _newID, int _TextureLocation)
	{
		_id = _newID;
		_textureLocation = _TextureLocation;
	}

	GLuint Texture::GetTexture()
	{
		return _id;
	}

	int Texture::GetTextureLocation()
	{
		return _textureLocation;
	}

	void Texture::BindTexture()
	{
		glActiveTexture(GL_TEXTURE0 + _textureLocation);
		glBindTexture(GL_TEXTURE_2D, _id);
	}

	void Texture::setWidth(int _newWidth)
	{
		_width = _newWidth;
	}

	void Texture::setheight(int _newHeight)
	{
		_height = _newHeight;
	}

	int Texture::getWidth()
	{
		return _width;
	}

	int Texture::getHeight()
	{
		return _height;
	}
}
