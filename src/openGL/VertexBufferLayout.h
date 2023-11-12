#pragma once

#include <stdexcept>
#include <vector>
#include <GL/glew.h>

struct VertexBufferElement
{
	GLuint count;
	GLenum type;
	GLboolean normalized;
	GLuint size;
};

class VertexBufferLayout
{
public:
	VertexBufferLayout();
	~VertexBufferLayout();

	void Push(GLuint count, GLenum type, GLboolean normalized, GLuint size);

	inline GLuint GetStride() const { return m_Stride; }
	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; }


private:
	std::vector<VertexBufferElement> m_Elements;
	GLuint m_Stride;
};
