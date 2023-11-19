#include "BlockMesh.h"

BlockMesh::BlockMesh(BlockType blockType)
	: m_BlockType(blockType)
{

    std::vector<Vertex> vertices;
    float texPos = 1.0f / 16.0f;
    float sideX(0.0f), upX(0.0f), bottomX(0.0f);
    float sideY(0.0f), upY(0.0f), bottomY(0.0f);

    switch (blockType)
    {
    case BlockType::GRASS:
    {
        sideX = texPos;
        sideY = texPos * 15;

        upX = texPos * 2;
        upY = texPos * 15;

        bottomX = 0.0f;
        bottomY = texPos * 15;
    }
        break;
    case BlockType::STONE:
    {
        sideX = texPos * 4;
        sideY = texPos * 15;

        upX = texPos * 4;
        upY = texPos * 15;

        bottomX = texPos * 4;
        bottomY = texPos * 15;
    }
        break;
    case BlockType::DIRT:
    {
        sideX = 0.0f;
        sideY = texPos * 15;

        upX = 0.0f;
        upY = texPos * 15;

        bottomX = 0.0f;
        bottomY = texPos * 15;
    }
        break;
    default:
        break;
    }


    // SIDE FACE
    vertices.push_back({ {0.0f, 0.0f, 1.0f}, {sideX, sideY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 0.0f, 1.0f}, {sideX + texPos , sideY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 1.0f, 1.0f}, {sideX + texPos, sideY + texPos}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {0.0f, 1.0f, 1.0f}, {sideX, sideY + texPos}, {0.0f, 0.0f, 0.0f} });

    vertices.push_back({ {0.0f, 0.0f, 0.0f}, {sideX + texPos, sideY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 0.0f, 0.0f}, {sideX, sideY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 1.0f, 0.0f}, {sideX, sideY + texPos}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {0.0f, 1.0f, 0.0f}, {sideX + texPos, sideY + texPos}, {0.0f, 0.0f, 0.0f} });

    // UP FACE
    vertices.push_back({ {0.0f, 1.0f, 1.0f}, {upX, upY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 1.0f, 1.0f}, {upX + texPos, upY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 1.0f, 0.0f}, {upX + texPos, upY + texPos}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {0.0f, 1.0f, 0.0f}, {upX, upY + texPos}, {0.0f, 0.0f, 0.0f} });

    // BOTTOM FACE
    vertices.push_back({ {0.0f, 0.0f, 1.0f}, {bottomX, bottomY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 0.0f, 1.0f}, {bottomX + texPos, bottomY}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 0.0f, 0.0f}, {bottomX + texPos, bottomY + texPos}, {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {0.0f, 0.0f, 0.0f}, {bottomX, bottomY + texPos}, {0.0f, 0.0f, 0.0f} });

    std::vector<GLuint> indices{
                        0, 1, 2,
                        2, 3, 0,
                        1, 5, 6,
                        6, 2, 1,
                        5, 4, 7,
                        7, 6, 5,
                        4, 0, 3,
                        3, 7, 4,
                        8, 9, 10,
                        10, 11, 8,
                        13, 12, 15,
                        15, 14, 13
    };

    m_Mesh = std::make_unique<Mesh>(vertices, indices);

    m_Material = std::make_unique<Material>("res/shaders/Block.shader", "res/textures/texture_pack.png");
}

BlockMesh::~BlockMesh()
{
}

void BlockMesh::Bind() const
{
    m_Mesh->Bind();
    m_Material->Bind();
}

void BlockMesh::Unbind() const
{
    m_Mesh->Unbind();
    m_Material->Unbind();
}

void BlockMesh::BindMesh() const
{
    m_Mesh->Bind();
}

void BlockMesh::BindMaterial() const
{
    m_Material->Bind();
}
