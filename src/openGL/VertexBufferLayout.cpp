#include "VertexBufferLayout.h"

VertexBufferLayout::VertexBufferLayout()
{
	m_Stride = 0;
}

VertexBufferLayout::~VertexBufferLayout()
{

}

void VertexBufferLayout::Push(GLuint count, GLenum type, GLboolean normalized, GLuint size)
{
	m_Elements.push_back(VertexBufferElement{ count, type, normalized, size });
	m_Stride += sizeof(type) * count;
}
