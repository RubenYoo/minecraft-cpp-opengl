#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer&, const VertexBufferLayout&);
	void Bind() const;
	void Unbind() const;

private:
	GLuint m_RendererID;
};
