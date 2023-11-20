#pragma once

#include "openGL/VertexArray.h"
#include "openGL/IndexBuffer.h"

#include "utils/glm/glm.hpp"
#include <GL/glew.h>
#include <vector>
#include <memory>

struct Vertex {
    glm::vec3 position;
};

struct Vertex2 : Vertex{
    glm::vec2 texCoords;

    Vertex2(const glm::vec3& pos, const glm::vec2& tex) : Vertex{ pos }, texCoords(tex) {}
};

struct Vertex3 : Vertex2 {
    glm::vec3 normal;

    Vertex3(const glm::vec3& pos, const glm::vec2& tex, const glm::vec3& norm)
        : Vertex2{ pos, tex }, normal(norm) {}
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices);
    Mesh(std::vector<Vertex3> vertices, std::vector<GLuint> indices);
    ~Mesh();
	
    void Bind() const;
    void Unbind() const;

    inline const VertexArray& GetVertexArray() const { return *m_VAO; }
    inline const IndexBuffer& GetIndexBuffer() const { return *m_EBO; }

private:
    std::vector<GLuint> m_Indices;
    
    std::unique_ptr<VertexArray> m_VAO;
    std::unique_ptr<VertexBufferLayout> m_VBL;
    std::unique_ptr<VertexBuffer> m_VBO;
    std::unique_ptr<IndexBuffer> m_EBO;
};
