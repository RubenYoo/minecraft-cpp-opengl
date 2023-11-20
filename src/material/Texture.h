#pragma once
#include <GL/glew.h>
#include <iostream>

class Texture
{
public:
	Texture(const std::string& filepath);
	~Texture();

	void Bind(GLuint slot = 0) const;
	void Unbind() const;

	inline GLint GetWidth() const { return m_Width; }
	inline GLint GetHeight() const { return m_Height; }
	inline GLint GetBPP() const { return m_BPP; }

private:
	GLuint m_RendererId;
	std::string m_FilePath;
	GLubyte* m_LocalBuffer;
	GLint m_Width, m_Height, m_BPP;
};

