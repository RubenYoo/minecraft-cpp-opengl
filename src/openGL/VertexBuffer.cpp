#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, GLuint size, GLenum typeDraw)
	: m_RendererID(0)
{
	glGenBuffers(GLsizei(1), &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, data, typeDraw);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(GLsizei(1), &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
