#pragma once

#include <memory>
#include "mesh/Mesh.h"
#include "PickingTexture.h"
#include "material/Shader.h"

class BlockPick
{
public:
	BlockPick();
	~BlockPick();

	void Bind() const;
	void Unbind() const;

	inline Shader& GetShader() const { return *m_Shader; }
	inline Mesh& GetMesh() const { return *m_Mesh; }

private:
	std::unique_ptr<Shader> m_Shader;
	std::unique_ptr<Mesh> m_Mesh;
};

