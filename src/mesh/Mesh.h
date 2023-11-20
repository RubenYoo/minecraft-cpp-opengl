#pragma once

#include "openGL/VertexArray.h"
#include "openGL/IndexBuffer.h"

#include "utils/glm/glm.hpp"
#include <GL/glew.h>
#include <vector>
#include <memory>

struct Vertex {
    glm::vec3 position;
    glm::vec2 texCoords;
    glm::vec3 normal;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    ~Mesh();
	
    void Bind() const;
    void Unbind() const;

    inline const VertexArray& GetVertexArray() const { return *m_VAO; }
    inline const IndexBuffer& GetIndexBuffer() const { return *m_EBO; }

private:
    std::vector<Vertex> m_Vertices;
    std::vector<GLuint> m_Indices;
    
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBufferLayout> m_VBL;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_EBO;
};
