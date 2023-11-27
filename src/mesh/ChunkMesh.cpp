#include <glm/gtc/matrix_transform.hpp>
#include "ChunkMesh.h"
#include "renderer/Renderer.h"

ChunkMesh::ChunkMesh()
	: m_SizeX(16), m_SizeY(16), m_SizeZ(16)
{
	m_Material = std::make_unique<Material>("assets/shaders/Block.shader", "assets/textures/texture_pack.png");

	for (size_t i = 0; i < m_SizeX; i++)
	{
		for (size_t j = 0; j < m_SizeY; j++)
		{
			for (size_t k = 0; k < m_SizeZ; k++)
			{
				if(j < 10)
					m_BlockData[i][j][k] = BlockType::STONE;
				else if (j == 15)
					m_BlockData[i][j][k] = BlockType::GRASS;
				else
					m_BlockData[i][j][k] = BlockType::DIRT;
			}
		}
	}

}

ChunkMesh::~ChunkMesh()
{
}

void ChunkMesh::GenerateChunk(glm::mat4 vp)
{
	Renderer renderer;
	std::vector<Vertex2> vertices;
	std::vector<GLuint> indices;
	size_t vertexOffset = 0;

	for (size_t i = 0; i < m_SizeX; i++)
	{
		for (size_t j = 0; j < m_SizeY; j++)
		{
			for (size_t k = 0; k < m_SizeZ; k++)
			{
				if(m_BlockData[i][j][k] != BlockType::AIR)
				{
					glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(i, j, k));

					std::set<BlockFace> faces = WhichFaceIsVisible(i, j, k);

					if (faces.size() != 0)
					{
						std::pair<BlockType, std::set<BlockFace>> myBlock = { m_BlockData[i][j][k], faces };

						if (m_BlockMeshes.find(myBlock) == m_BlockMeshes.end())
							m_BlockMeshes[myBlock] = std::make_unique<BlockMesh>(m_BlockData[i][j][k], faces);
						

						std::vector<Vertex2> blockVertices = m_BlockMeshes[myBlock]->GetVertices();

						for (Vertex2& vertex : blockVertices)
						{
							// Apply translation
							vertex.position.x += i;
							vertex.position.y += j;
							vertex.position.z += k;
							vertices.push_back(vertex); 
						}

						for (GLuint index : m_BlockMeshes[myBlock]->GetIndices())
						{
							indices.push_back(index + static_cast<GLuint>(vertexOffset));
						}

						vertexOffset += blockVertices.size();
					}
				}
			}
		}
	}

	m_Material->Bind();
	Mesh chunkMesh(vertices, indices);
	m_Material->GetShader().SetUniformMat4f("u_MVP", vp);
	m_Material->GetShader().SetUniform3f("u_BorderColor", 0.0, 0.0, 0.0);
	m_Material->GetShader().SetUniform1f("u_BorderThickness", 0.0);

	renderer.Draw(chunkMesh.GetVertexArray(), chunkMesh.GetIndexBuffer(), m_Material->GetShader());

}

std::set<BlockFace> ChunkMesh::WhichFaceIsVisible(size_t x, size_t y, size_t z)
{
	std::set<BlockFace> visibleFaces;

	if (x > 0)
	{
		if (m_BlockData[x - 1][y][z] == BlockType::AIR)
			visibleFaces.insert(BlockFace::LEFT);
	}
	else
		visibleFaces.insert(BlockFace::LEFT);


	if (x + 1 < m_SizeX)
	{
		if (m_BlockData[x + 1][y][z] == BlockType::AIR)
			visibleFaces.insert(BlockFace::RIGHT);
	}
	else
		visibleFaces.insert(BlockFace::RIGHT);
	

	if(y > 0)
	{
		if (m_BlockData[x][y - 1][z] == BlockType::AIR)
			visibleFaces.insert(BlockFace::DOWN);
	}
	else
		visibleFaces.insert(BlockFace::DOWN);

	if (y + 1 < m_SizeY)
	{
		if (m_BlockData[x][y + 1][z] == BlockType::AIR)
			visibleFaces.insert(BlockFace::UP);
	}
	else
		visibleFaces.insert(BlockFace::UP);

	
	if (z > 0)
	{
		if (m_BlockData[x][y][z - 1] == BlockType::AIR)
			visibleFaces.insert(BlockFace::FRONT);
	}

	else
		visibleFaces.insert(BlockFace::FRONT);

	
	if (z + 1 < m_SizeZ)
	{
		if (m_BlockData[x][y][z + 1] == BlockType::AIR)
			visibleFaces.insert(BlockFace::BACK);
	}
	else
		visibleFaces.insert(BlockFace::BACK);


	return visibleFaces;
}
