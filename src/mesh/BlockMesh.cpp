#include "BlockMesh.h"

BlockMesh::BlockMesh(BlockType blockType, std::set<BlockFace> blockFaces)
	: m_BlockType(blockType)
{

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
        m_Vertices.push_back({ {0.0f, 0.0f, 1.0f}, {sideX, sideY} });
        m_Vertices.push_back({ {1.0f, 0.0f, 1.0f}, {sideX + texPos , sideY} });
        m_Vertices.push_back({ {1.0f, 1.0f, 1.0f}, {sideX + texPos, sideY + texPos} });
        m_Vertices.push_back({ {0.0f, 1.0f, 1.0f}, {sideX, sideY + texPos} });

        m_Indices.push_back(0 + offset);
        m_Indices.push_back(1 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(3 + offset);
        m_Indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::RIGHT) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        m_Vertices.push_back({ {1.0f, 0.0f, 1.0f}, {sideX, sideY} });
        m_Vertices.push_back({ {1.0f, 0.0f, 0.0f}, {sideX + texPos , sideY} });
        m_Vertices.push_back({ {1.0f, 1.0f, 0.0f}, {sideX + texPos, sideY + texPos} });
        m_Vertices.push_back({ {1.0f, 1.0f, 1.0f}, {sideX, sideY + texPos} });

        m_Indices.push_back(0 + offset);
        m_Indices.push_back(1 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(3 + offset);
        m_Indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::FRONT) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        m_Vertices.push_back({ {1.0f, 0.0f, 0.0f}, {sideX, sideY} });
        m_Vertices.push_back({ {0.0f, 0.0f, 0.0f}, {sideX + texPos , sideY} });
        m_Vertices.push_back({ {0.0f, 1.0f, 0.0f}, {sideX + texPos, sideY + texPos} });
        m_Vertices.push_back({ {1.0f, 1.0f, 0.0f}, {sideX, sideY + texPos} });

        m_Indices.push_back(0 + offset);
        m_Indices.push_back(1 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(3 + offset);
        m_Indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::LEFT) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        m_Vertices.push_back({ {0.0f, 0.0f, 0.0f}, {sideX, sideY} });
        m_Vertices.push_back({ {0.0f, 0.0f, 1.0f}, {sideX + texPos , sideY} });
        m_Vertices.push_back({ {0.0f, 1.0f, 1.0f}, {sideX + texPos, sideY + texPos} });
        m_Vertices.push_back({ {0.0f, 1.0f, 0.0f}, {sideX, sideY + texPos} });

        m_Indices.push_back(0 + offset);
        m_Indices.push_back(1 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(3 + offset);
        m_Indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::UP) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        m_Vertices.push_back({ {0.0f, 1.0f, 1.0f}, {upX, upY} });
        m_Vertices.push_back({ {1.0f, 1.0f, 1.0f}, {upX + texPos, upY} });
        m_Vertices.push_back({ {1.0f, 1.0f, 0.0f}, {upX + texPos, upY + texPos} });
        m_Vertices.push_back({ {0.0f, 1.0f, 0.0f}, {upX, upY + texPos} });

        m_Indices.push_back(0 + offset);
        m_Indices.push_back(1 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(3 + offset);
        m_Indices.push_back(0 + offset);

        offset += 4;
    }

    if (blockFaces.find(BlockFace::DOWN) != blockFaces.end() || blockFaces.find(BlockFace::ALL) != blockFaces.end())
    {
        m_Vertices.push_back({ {0.0f, 0.0f, 0.0f}, {bottomX, bottomY} });
        m_Vertices.push_back({ {1.0f, 0.0f, 0.0f}, {bottomX + texPos, bottomY} });
        m_Vertices.push_back({ {1.0f, 0.0f, 1.0f}, {bottomX + texPos, bottomY + texPos} });
        m_Vertices.push_back({ {0.0f, 0.0f, 1.0f}, {bottomX, bottomY + texPos} });

        m_Indices.push_back(0 + offset);
        m_Indices.push_back(1 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(2 + offset);
        m_Indices.push_back(3 + offset);
        m_Indices.push_back(0 + offset);

        offset += 4;
    }

}

BlockMesh::~BlockMesh()
{
}

