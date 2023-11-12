#include "IndexBuffer.h"


IndexBuffer::IndexBuffer(const unsigned int* data, GLuint count, GLenum typeDraw)
	: m_Count(count)
{
	glGenBuffers(GLsizei(1), &m_RendererID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, typeDraw);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(GLsizei(1), &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
