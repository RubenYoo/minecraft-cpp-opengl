#pragma once

#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(std::string shader, std::string texture);
	~Material();

	void Bind() const;
	void Unbind() const;

	inline Shader& GetShader() const { return *m_Shader; }
	inline Texture& GetTexture() const { return *m_Texture; }

private:
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr <Texture> m_Texture;
};
