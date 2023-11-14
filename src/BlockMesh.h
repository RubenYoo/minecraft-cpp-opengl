#pragma once

#include <glm/glm.hpp>

#include "Mesh.h"
#include "Material.h"

enum class BlockType
{
	GRASS,
	DIRT,
	STONE
};


class BlockMesh
{
public:
	BlockMesh(BlockType blockType);
	~BlockMesh();

	void Bind() const;
	void Unbind() const;

	inline const Material& GetMaterial() const { return *m_Material; }
	inline const Mesh& GetMesh() const { return *m_Mesh; }

private:
	BlockType m_BlockType;
	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Material> m_Material;
};
