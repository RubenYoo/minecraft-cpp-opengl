#pragma once

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:

};

