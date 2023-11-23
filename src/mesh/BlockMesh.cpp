#include "BlockMesh.h"

BlockMesh::BlockMesh(BlockType blockType, Material& material, std::set<BlockFace> blockFaces)
	: m_BlockType(blockType)
{

    std::vector<Vertex2> vertices;
    std::vector<GLuint> indices;

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
    
    size_t offset = 0;

    if (blockFaces.find(BlockFace::BACK) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        vertices.push_back({ {0.0f, 0.0f, 1.0f}, {sideX, sideY} });
        vertices.push_back({ {1.0f, 0.0f, 1.0f}, {sideX + texPos , sideY} });
        vertices.push_back({ {1.0f, 1.0f, 1.0f}, {sideX + texPos, sideY + texPos} });
        vertices.push_back({ {0.0f, 1.0f, 1.0f}, {sideX, sideY + texPos} });

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);
        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::RIGHT) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        vertices.push_back({ {1.0f, 0.0f, 1.0f}, {sideX, sideY} });
        vertices.push_back({ {1.0f, 0.0f, 0.0f}, {sideX + texPos , sideY} });
        vertices.push_back({ {1.0f, 1.0f, 0.0f}, {sideX + texPos, sideY + texPos} });
        vertices.push_back({ {1.0f, 1.0f, 1.0f}, {sideX, sideY + texPos} });

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);
        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::FRONT) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        vertices.push_back({ {1.0f, 0.0f, 0.0f}, {sideX, sideY} });
        vertices.push_back({ {0.0f, 0.0f, 0.0f}, {sideX + texPos , sideY} });
        vertices.push_back({ {0.0f, 1.0f, 0.0f}, {sideX + texPos, sideY + texPos} });
        vertices.push_back({ {1.0f, 1.0f, 0.0f}, {sideX, sideY + texPos} });

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);
        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::LEFT) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        vertices.push_back({ {0.0f, 0.0f, 0.0f}, {sideX, sideY} });
        vertices.push_back({ {0.0f, 0.0f, 1.0f}, {sideX + texPos , sideY} });
        vertices.push_back({ {0.0f, 1.0f, 1.0f}, {sideX + texPos, sideY + texPos} });
        vertices.push_back({ {0.0f, 1.0f, 0.0f}, {sideX, sideY + texPos} });

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);
        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::UP) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        vertices.push_back({ {0.0f, 1.0f, 1.0f}, {upX, upY} });
        vertices.push_back({ {1.0f, 1.0f, 1.0f}, {upX + texPos, upY} });
        vertices.push_back({ {1.0f, 1.0f, 0.0f}, {upX + texPos, upY + texPos} });
        vertices.push_back({ {0.0f, 1.0f, 0.0f}, {upX, upY + texPos} });

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);
        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::DOWN) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        vertices.push_back({ {0.0f, 0.0f, 0.0f}, {bottomX, bottomY} });
        vertices.push_back({ {1.0f, 0.0f, 0.0f}, {bottomX + texPos, bottomY} });
        vertices.push_back({ {1.0f, 0.0f, 1.0f}, {bottomX + texPos, bottomY + texPos} });
        vertices.push_back({ {0.0f, 0.0f, 1.0f}, {bottomX, bottomY + texPos} });

        indices.push_back(0 + offset);
        indices.push_back(1 + offset);
        indices.push_back(2 + offset);
        indices.push_back(2 + offset);
        indices.push_back(3 + offset);
        indices.push_back(0 + offset);

        offset += 4;
    }

    m_Mesh = std::make_unique<Mesh>(vertices, indices);

    m_Material = &material;
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

