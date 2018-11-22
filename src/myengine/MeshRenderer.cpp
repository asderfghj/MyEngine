#include "MeshRenderer.h"
#include "Shader.h"
#include "Entity.h"
#include "Transform.h"
#include "Core.h"
#include "Camera.h"
#include "Texture.h"
#include "Model.h"


namespace frontier
{
	void MeshRenderer::OnInit(std::weak_ptr<Entity> _parent, std::shared_ptr<Model> meshData)
	{
		Component::OnInit(_parent);
		Copyable = true;
		_meshData = meshData;
	}

	void MeshRenderer::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<MeshRenderer> _original)
	{
		Component::OnInit(_parent);
		Copyable = true;
		_meshData = _original.lock()->getMeshData();
		_shaderProgram = _original.lock()->getShader();
		_texture = _original.lock()->getTexture();
	}

	void MeshRenderer::OnTick()
	{
		Component::OnTick();
		_meshData->Draw(getEntity()->getComponent<Transform>()->getModelMatrix(), getCore()->getMainCamera()->getViewMatrix(), getCore()->getMainCamera()->getProjectionMatrix(), _texture, _shaderProgram);

	}

	void MeshRenderer::AttachShaderProgram(std::shared_ptr<Shader> _newShaderProgram)
	{
		_shaderProgram = _newShaderProgram;
	}

	void MeshRenderer::AttachTexture(std::shared_ptr<Texture> _newTexture)
	{
		_texture = _newTexture;
	}

	std::shared_ptr<Model> MeshRenderer::getMeshData()
	{
		return _meshData;
	}

	std::shared_ptr<Texture> MeshRenderer::getTexture()
	{
		return _texture;
	}

	std::shared_ptr<Shader> MeshRenderer::getShader()
	{
		return _shaderProgram;
	}

}