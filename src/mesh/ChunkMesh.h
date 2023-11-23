#pragma once

#include <vector>
#include <memory>
#include <map>
#include <glm/glm.hpp>
#include "BlockMesh.h"

class ChunkMesh
{
public:
	ChunkMesh();
	~ChunkMesh();

	void GenerateChunk(glm::mat4 vp);
	std::set<BlockFace> WhichFaceIsVisible(size_t x, size_t y, size_t z);

private:
	std::unique_ptr<Material> m_Material;
	BlockType m_BlockData[16][16][32];
	std::map<std::pair<BlockType, std::set<BlockFace>>, std::unique_ptr<BlockMesh>> m_BlockMeshes;

	unsigned int m_SizeX;
	unsigned int m_SizeY;
	unsigned int m_SizeZ;
};
