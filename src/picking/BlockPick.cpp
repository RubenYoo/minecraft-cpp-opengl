#include "BlockPick.h"

BlockPick::BlockPick()
{
    std::vector<Vertex> vertices;

    vertices.push_back({ {0.0f, 0.0f, 1.0f} });
    vertices.push_back({ {1.0f, 0.0f, 1.0f} });
    vertices.push_back({ {1.0f, 1.0f, 1.0f} });
    vertices.push_back({ {0.0f, 1.0f, 1.0f} });
                                             
    vertices.push_back({ {0.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 0.0f, 0.0f} });
    vertices.push_back({ {1.0f, 1.0f, 0.0f} });
    vertices.push_back({ {0.0f, 1.0f, 0.0f} });

    std::vector<GLuint> indices{
        0, 1, 2,
        2, 3, 0,
        1, 5, 6,
        6, 2, 1,
        5, 4, 7,
        7, 6, 5,
        4, 0, 3,
        3, 7, 4,
        3, 2, 6,
        6, 7, 3,
        4, 5, 1,
        1, 0, 4                
    };

    m_Mesh = std::make_unique<Mesh>(vertices, indices);
    m_Shader = std::make_unique<Shader>("assets/shaders/Picking.shader");        
}

BlockPick::~BlockPick()
{

}

void BlockPick::Bind() const
{
    m_Shader->Bind();
    m_Mesh->Bind();
}

void BlockPick::Unbind() const
{
    m_Shader->Unbind();
    m_Mesh->Unbind();
}
