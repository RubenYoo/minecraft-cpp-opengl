#pragma once

#include "openGL/IndexBuffer.h"
#include "openGL/VertexArray.h"
#include <glm/glm.hpp>
#include "./camera/Camera.h"
#include "material/Shader.h"
#include "mesh/BlockMesh.h"
#include "mesh/CursorMesh.h"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Clear() const;
	void DrawBlock(const BlockMesh& blockMesh, glm::mat4 vp, glm::mat4 model, bool selected) const;
	void DrawCursor(const CursorMesh& cursorMesh, glm::mat4 vp, glm::mat4 model) const;
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

	//void PickBlock(const BlockMesh& blockMesh, glm::mat4 vp, glm::mat4 model) const;

private:

};

