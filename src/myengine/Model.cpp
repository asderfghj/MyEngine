#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Model.h"
#include "Mesh.h"

#include <iostream>


namespace frontier
{
	Model::Model()
	{
		std::cout << "Model component created" << std::endl;
	}

	std::shared_ptr<Model> Model::Create(const char *path, std::weak_ptr<Resources> _resources)
	{
		std::shared_ptr<Model> rtn = std::make_shared<Model>();
		rtn->loadModel(path);
		_resources.lock()->AddCreatedResource(rtn);
		return rtn;
	}

	void Model::Draw(glm::mat4 _model, glm::mat4 _view, glm::mat4 _proj, std::shared_ptr<Texture> _tex, std::shared_ptr<Shader> _shader)
	{
		for (size_t i = 0; i < meshes.size(); i++)
		{
			meshes[i]->Draw(_model, _view, _proj, _tex, _shader);
		}
	}

	void Model::loadModel(std::string path)
	{
		tinyobj::attrib_t inAttrib;
		std::vector<tinyobj::shape_t> inShapes;
		std::vector<tinyobj::material_t> inMats;
		std::string errorMsg;
		int basePathEndIndex;
		bool hasTexCoords = true;

		for (size_t i = 0; i < path.size(); i++)
		{
			if (path[i] == '/')
			{
				basePathEndIndex = i;
			}
		}

		tinyobj::LoadObj(&inAttrib, &inShapes, &inMats, &errorMsg, path.c_str(), path.substr(0, basePathEndIndex + 1).c_str());
		
		

		if (!errorMsg.empty())
		{
			std::cout << errorMsg << std::endl;
		}
		
		std::vector<GLfloat> vertices;
		std::vector<GLfloat> normals;
		std::vector<GLfloat> texCoords;

		for (unsigned int i = 0; i < inShapes.size(); i++)
		{
			for (unsigned int j = 0; j < inShapes[i].mesh.indices.size(); j++)
			{
				int indicesIndex = inShapes[i].mesh.indices[j].vertex_index * 3;
				vertices.push_back(inAttrib.vertices[indicesIndex]);
				vertices.push_back(inAttrib.vertices[indicesIndex + 1]);
				vertices.push_back(inAttrib.vertices[indicesIndex + 2]);

				int normalIndex = inShapes[i].mesh.indices[j].normal_index * 3;
				normals.push_back(inAttrib.normals[normalIndex]);
				normals.push_back(inAttrib.normals[normalIndex + 1]);
				normals.push_back(inAttrib.normals[normalIndex + 2]);

				if (hasTexCoords)
				{
					int texCoordsIndex = inShapes[i].mesh.indices[j].texcoord_index * 2;
					if (texCoordsIndex > -1)
					{
						texCoords.push_back(inAttrib.texcoords[texCoordsIndex]);
						texCoords.push_back(inAttrib.texcoords[texCoordsIndex + 1]);
					}
					else
					{
						hasTexCoords = false;
					}
				}
			}

			std::shared_ptr<Mesh> mesh;

			if (hasTexCoords)
			{
				mesh = std::make_shared<Mesh>(vertices, normals, texCoords);
			}
			else
			{
				mesh = std::make_shared<Mesh>(vertices, normals);
			}

			meshes.push_back(mesh);

		}

		std::cout << "Model Processed" << std::endl;

	}


}
