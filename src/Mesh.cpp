#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices)
	: m_Vertices(std::move(vertices)), m_Indices(std::move(indices))
{
	m_VAO = std::make_unique<VertexArray>();
	m_VBL = std::make_unique<VertexBufferLayout>();

	m_VBL->Push(GLuint(3), GL_FLOAT, GL_FALSE, sizeof(float) * 3);
	m_VBL->Push(GLuint(2), GL_FLOAT, GL_FALSE, sizeof(float) * 2);
	m_VBL->Push(GLuint(3), GL_FLOAT, GL_FALSE, sizeof(float) * 3);

	m_VBO = std::make_unique<VertexBuffer>(m_Vertices.data(), m_Vertices.size() * sizeof(Vertex), GL_STATIC_DRAW);

	m_VAO->AddBuffer(*m_VBO, *m_VBL);

	m_EBO = std::make_unique<IndexBuffer>(m_Indices.data(), m_Indices.size(), GL_STATIC_DRAW);

}

Mesh::~Mesh()
{
}
