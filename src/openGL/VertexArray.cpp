#include "VertexArray.h"

VertexArray::VertexArray()
	: m_RendererID(NULL)
{
	glGenVertexArrays(GLsizei(1), &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(GLsizei(1), &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	
	const auto& elements = layout.GetElements();

	GLuint offset = 0;

	for (size_t i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		glEnableVertexAttribArray(GLuint(i));
		glVertexAttribPointer(GLuint(i), GLuint(element.count), element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * sizeof(element.type);
	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
