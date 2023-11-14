#include "BlockMesh.h"

BlockMesh::BlockMesh(BlockType blockType)
	: m_BlockType(blockType)
{
    float texPos = 1.0f / 16.0f;

    std::vector<Vertex> vertices;

    switch (blockType)
    {
    case BlockType::GRASS:
    {
        //sides
        vertices.push_back({ {-0.5f, -0.5f, 0.5f}, {texPos, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, 0.5f}, {texPos * 2 , texPos * 15}, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, 0.5f}, {texPos * 2, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  0.5f, 0.5f}, {texPos, texPos * 16}, {0.0f, 0.0f, 0.0f} });

        vertices.push_back({ {-0.5f, -0.5f, -0.5f}, {texPos * 2, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, -0.5f}, {texPos, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f,  0.5f, -0.5f}, {texPos, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  0.5f, -0.5f}, {texPos * 2, texPos * 16}, {0.0f, 0.0f, 0.0f} });

        //front
        vertices.push_back({ {-0.5f,  0.5f, 0.5f}, {texPos * 2, texPos * 15 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, 0.5f}, {texPos * 3, texPos * 15 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, -0.5f}, {texPos * 3, texPos * 16 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {-0.5f,  0.5f, -0.5f}, {texPos * 2, texPos * 16 }, { 0.0f, 0.0f, 0.0f } });

        //bottom
        vertices.push_back({ {-0.5f, -0.5f, 0.5f}, {0, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, 0.5f}, {texPos, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, -0.5f}, {texPos, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  -0.5f, -0.5f}, {0, texPos * 16}, {0.0f, 0.0f, 0.0f} });

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
                            12, 13, 14,
                            14, 15, 12
        };

        m_Mesh = std::make_unique<Mesh>(vertices, indices);

    }
        break;
    case BlockType::STONE:
    {
        //sides
        vertices.push_back({ {-0.5f, -0.5f, 0.5f}, {texPos * 4, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, 0.5f}, {texPos * 5 , texPos * 15}, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, 0.5f}, {texPos * 5, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  0.5f, 0.5f}, {texPos * 4, texPos * 16}, {0.0f, 0.0f, 0.0f} });

        vertices.push_back({ {-0.5f, -0.5f, -0.5f}, {texPos * 5, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, -0.5f}, {texPos * 4, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f,  0.5f, -0.5f}, {texPos * 4, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  0.5f, -0.5f}, {texPos * 5, texPos * 16}, {0.0f, 0.0f, 0.0f} });

        //front
        vertices.push_back({ {-0.5f,  0.5f, 0.5f}, {texPos * 4, texPos * 15 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, 0.5f}, {texPos * 5, texPos * 15 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, -0.5f}, {texPos * 5, texPos * 16 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {-0.5f,  0.5f, -0.5f}, {texPos * 4, texPos * 16 }, { 0.0f, 0.0f, 0.0f } });

        //bottom
        vertices.push_back({ {-0.5f, -0.5f, 0.5f}, {texPos * 4, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, 0.5f}, {texPos * 5, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, -0.5f}, {texPos * 5, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  -0.5f, -0.5f}, {texPos * 4, texPos * 16}, {0.0f, 0.0f, 0.0f} });

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
                            12, 13, 14,
                            14, 15, 12
        };

        m_Mesh = std::make_unique<Mesh>(vertices, indices);
    }
        break;
    case BlockType::DIRT:
    {
        //sides
        vertices.push_back({ {-0.5f, -0.5f, 0.5f}, {0, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, 0.5f}, {texPos , texPos * 15}, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, 0.5f}, {texPos, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  0.5f, 0.5f}, {0, texPos * 16}, {0.0f, 0.0f, 0.0f} });

        vertices.push_back({ {-0.5f, -0.5f, -0.5f}, {texPos, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, -0.5f}, {0, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f,  0.5f, -0.5f}, {0, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  0.5f, -0.5f}, {texPos, texPos * 16}, {0.0f, 0.0f, 0.0f} });

        //front
        vertices.push_back({ {-0.5f,  0.5f, 0.5f}, {0, texPos * 15 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, 0.5f}, {texPos, texPos * 15 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {0.5f,  0.5f, -0.5f}, {texPos, texPos * 16 }, { 0.0f, 0.0f, 0.0f } });
        vertices.push_back({ {-0.5f,  0.5f, -0.5f}, {0, texPos * 16 }, { 0.0f, 0.0f, 0.0f } });

        //bottom
        vertices.push_back({ {-0.5f, -0.5f, 0.5f}, {0, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, 0.5f}, {texPos, texPos * 15}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {0.5f, -0.5f, -0.5f}, {texPos, texPos * 16}, {0.0f, 0.0f, 0.0f} });
        vertices.push_back({ {-0.5f,  -0.5f, -0.5f}, {0, texPos * 16}, {0.0f, 0.0f, 0.0f} });

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
                            12, 13, 14,
                            14, 15, 12
        };

        m_Mesh = std::make_unique<Mesh>(vertices, indices);
    }
        break;
    default:
        break;
    }


    m_Material = std::make_unique<Material>("res/shaders/Basic.shader", "res/textures/texture_pack.png");
}

BlockMesh::~BlockMesh()
{
}

void BlockMesh::Bind() const
{
    m_Material->Bind();
}

void BlockMesh::Unbind() const
{
    m_Material->Unbind();
}
