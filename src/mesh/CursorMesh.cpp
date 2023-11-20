#include "CursorMesh.h"

CursorMesh::CursorMesh()
{
    std::vector<Vertex3> vertices;

    vertices.push_back({ {0.0f,  0.0f + 12.0f, 1.0f}, {48.0f / 256.0f, 246.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {32.0f, 0.0f + 12.0f, 1.0f}, {64.0f / 256.0f ,246.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {32.0f, 8.0f + 12.0f, 1.0f}, {64.0f / 256.0f, 250.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {0.0f,  8.0f + 12.0f, 1.0f}, {48.0f / 256.0f, 250.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });

    vertices.push_back({ {0.0f + 12.0f, 0.0f,  1.0f}, {54.0f / 256.0f, 240.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {8.0f + 12.0f, 0.0f,  1.0f}, {58.0f / 256.0f, 240.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {8.0f + 12.0f, 32.0f, 1.0f}, {58.0f / 256.0f, 256.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {0.0f + 12.0f, 32.0f, 1.0f}, {54.0f / 256.0f, 256.0f / 256.0f}, {0.0f, 0.0f, 0.0f} });


    std::vector<GLuint> indices = {
        0, 1, 2,
        2, 3, 0,
        4, 5, 6,
        6, 7, 4
    };


    m_Mesh = std::make_unique<Mesh>(vertices, indices);
    m_Material = std::make_unique<Material>("assets/shaders/Cursor.shader", "assets/textures/texture_pack.png");
}

CursorMesh::~CursorMesh()
{
}

void CursorMesh::Bind() const
{
    m_Mesh->Bind();
    m_Material->Bind();
}

void CursorMesh::Unbind() const
{
    m_Mesh->Unbind();
    m_Material->Unbind();
}
