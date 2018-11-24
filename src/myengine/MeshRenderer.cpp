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
		m_copyable = true;
		m_meshData = meshData;
	}

	void MeshRenderer::OnInit(std::weak_ptr<Entity> _parent, std::weak_ptr<MeshRenderer> _original)
	{
		Component::OnInit(_parent);
		m_copyable = true;
		m_meshData = _original.lock()->GetMeshData();
		m_shaderProgram = _original.lock()->GetShader();
		m_texture = _original.lock()->GetTexture();
	}

	void MeshRenderer::OnTick()
	{
		Component::OnTick();
		m_meshData->Draw(GetEntity()->getComponent<Transform>()->GetModelMatrix(), GetCore()->GetMainCamera()->GetViewMatrix(), GetCore()->GetMainCamera()->GetProjectionMatrix(), m_texture, m_shaderProgram);

	}

	void MeshRenderer::AttachShaderProgram(std::shared_ptr<Shader> _newShaderProgram)
	{
		m_shaderProgram = _newShaderProgram;
	}

	void MeshRenderer::AttachTexture(std::shared_ptr<Texture> _newTexture)
	{
		m_texture = _newTexture;
	}

	std::shared_ptr<Model> MeshRenderer::GetMeshData()
	{
		return m_meshData;
	}

	std::shared_ptr<Texture> MeshRenderer::GetTexture()
	{
		return m_texture;
	}

	std::shared_ptr<Shader> MeshRenderer::GetShader()
	{
		return m_shaderProgram;
	}

}