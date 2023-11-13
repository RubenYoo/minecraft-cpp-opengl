#pragma once

#include "Shader.h"
#include "Texture.h"

class Material
{
public:
	Material(Shader shader, Texture texture);
	~Material();

	void Bind() const;
	void Unbind() const;

	inline Shader& GetShader() { return m_Shader; }
	inline Texture& GetTexture() { return m_Texture; }

private:
	Shader m_Shader;
	Texture m_Texture;
};
