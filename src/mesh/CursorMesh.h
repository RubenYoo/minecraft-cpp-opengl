#pragma once

#include "Mesh.h"
#include "material/Material.h"

class CursorMesh
{
public:
	CursorMesh();
	~CursorMesh();

	void Bind() const;
	void Unbind() const;

	inline const Material& GetMaterial() const { return *m_Material; }
	inline const Mesh& GetMesh() const { return *m_Mesh; }

private:
	std::unique_ptr<Mesh> m_Mesh;
	std::unique_ptr<Material> m_Material;
};
