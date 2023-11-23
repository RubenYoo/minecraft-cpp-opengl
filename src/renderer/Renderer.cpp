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

void Renderer::DrawBlock(const BlockMesh& blockMesh, glm::mat4 vp, glm::mat4 model, bool selected) const
{
	blockMesh.Bind();

	glm::mat4 mvp = vp * model;

	blockMesh.GetMaterial().GetShader().SetUniformMat4f("u_MVP", mvp);
	blockMesh.GetMaterial().GetShader().SetUniform3f("u_BorderColor", 0.0, 0.0, 0.0);

	if (selected)
		blockMesh.GetMaterial().GetShader().SetUniform1f("u_BorderThickness", 1.0);
	else
		blockMesh.GetMaterial().GetShader().SetUniform1f("u_BorderThickness", 0.0);

	Draw(blockMesh.GetMesh().GetVertexArray(), blockMesh.GetMesh().GetIndexBuffer(), blockMesh.GetMaterial().GetShader());

	blockMesh.Unbind();
}

void Renderer::DrawCursor(const CursorMesh& cursorMesh, glm::mat4 vp, glm::mat4 model) const
{
	cursorMesh.Bind();

	glm::mat4 mvp = vp * model;

	cursorMesh.GetMaterial().GetShader().SetUniformMat4f("u_MVP", mvp);

	Draw(cursorMesh.GetMesh().GetVertexArray(), cursorMesh.GetMesh().GetIndexBuffer(), cursorMesh.GetMaterial().GetShader());
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	glDrawElements(GL_TRIANGLES, GLint(ib.GetCount()), GL_UNSIGNED_INT, nullptr);
}

void Renderer::PickBlock(const BlockPick& blockPick, glm::mat4 vp, glm::mat4 model, GLuint index) const
{
	blockPick.Bind();

	glm::mat4 mvp = vp * model;

	blockPick.GetShader().SetUniformMat4f("u_MVP", mvp);
	blockPick.GetShader().SetUniform1ui("u_ObjectIndex", index);

	Draw(blockPick.GetMesh().GetVertexArray(), blockPick.GetMesh().GetIndexBuffer(), blockPick.GetShader());

	//blockPick.Unbind();
}
