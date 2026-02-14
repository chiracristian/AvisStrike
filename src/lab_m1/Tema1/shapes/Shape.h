#pragma once

#include <vector>
#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

class Shape
{
public:
	Shape(unsigned drawMode = GL_TRIANGLES);

	Shape(const std::vector<VertexFormat>& vertices,
		const std::vector<unsigned>& indices,
		unsigned drawMode = GL_TRIANGLES);

	void applyTransform(const glm::mat3& transformMatrix);

	void merge(const Shape& shape);
	Mesh* convertToMesh(const std::string& name) const;

private:
	std::vector<VertexFormat> vertices;
	std::vector<unsigned> indices;
	unsigned drawMode;
};
