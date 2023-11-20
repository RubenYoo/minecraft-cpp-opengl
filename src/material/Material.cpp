#include "Material.h"

Material::Material(std::string shader, std::string texture)
{
	m_Shader = std::make_unique<Shader>(shader);
	m_Texture = std::make_unique<Texture>(texture);
}

Material::~Material()
{
}

void Material::Bind() const
{
	m_Shader->Bind();
	m_Texture->Bind();
}

void Material::Unbind() const
{
	m_Shader->Unbind();
	m_Texture->Unbind();
}
