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
	BlockMesh(BlockType blockType, Material& material, std::set<BlockFace> blockFaces = { BlockFace::ALL});
	~BlockMesh();

	void Bind() const;
	void Unbind() const;
	void BindMesh() const;
	void BindMaterial() const;


	inline const Material& GetMaterial() const { return *m_Material; }
	inline const Mesh& GetMesh() const { return *m_Mesh; }

private:
	BlockType m_BlockType;

	std::unique_ptr<Mesh> m_Mesh;
	Material* m_Material;
};
