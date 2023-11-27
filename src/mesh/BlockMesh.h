#pragma once

#include <glm/glm.hpp>
#include <set>
#include "Mesh.h"
#include "material/Material.h"

enum class BlockType
{
	AIR,
	GRASS,
	DIRT,
	STONE
};

enum class BlockFace
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	BACK,
	FRONT,
	ALL
};


class BlockMesh
{
public:
	BlockMesh(BlockType blockType, std::set<BlockFace> blockFaces = { BlockFace::ALL});
	~BlockMesh();

	inline std::vector<Vertex2> GetVertices() const { return m_Vertices; }
	inline std::vector<GLuint> GetIndices() const { return m_Indices; }

private:
	BlockType m_BlockType;
	std::vector<Vertex2> m_Vertices;
	std::vector<GLuint> m_Indices;
};
