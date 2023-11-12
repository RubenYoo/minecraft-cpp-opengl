#pragma once
#include<GL/glew.h>

class IndexBuffer
{
public:
	IndexBuffer(const unsigned int* data, GLuint count, GLenum typeDraw);
	~IndexBuffer();
	void Bind() const;
	void Unbind() const;

	inline GLuint GetCount() const { return m_Count; }

private:
	GLuint m_RendererID;
	GLuint m_Count;
};

