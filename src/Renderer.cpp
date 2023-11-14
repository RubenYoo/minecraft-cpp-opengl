#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::DrawBlock(const BlockMesh& blockMesh) const
{
	Draw(blockMesh.GetMesh().GetVertexArray(), blockMesh.GetMesh().GetIndexBuffer(), blockMesh.GetMaterial().GetShader());
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, GLint(ib.GetCount()), GL_UNSIGNED_INT, nullptr);
}
