#include "Material.h"

Material::Material(Shader shader, Texture texture)
	: m_Shader(shader), m_Texture(texture)
{
}

Material::~Material()
{
}

void Material::Bind() const
{
	m_Shader.Bind();
	m_Texture.Bind();
}

void Material::Unbind() const
{
	m_Shader.Unbind();
	m_Texture.Unbind();
}
