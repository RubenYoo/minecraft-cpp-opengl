#pragma once

#include "openGL/IndexBuffer.h"
#include "openGL/VertexArray.h"
#include "Shader.h"
#include "BlockMesh.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void DrawBlock(const BlockMesh& blockMesh) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:

};

