#include "Shape.h"
#include <algorithm>
#include "../Constants.h"

Shape::Shape(unsigned drawMode)
	: drawMode(drawMode)
{
	
}

Shape::Shape(
	const std::vector<VertexFormat>& vertices,
	const std::vector<unsigned>& indices,
	unsigned drawMode)
	: vertices(vertices), indices(indices), drawMode(drawMode)
{
	
}

void Shape::applyTransform(const glm::mat3& transformMatrix)
{
	for (VertexFormat& vertex : vertices) {
		vertex.position = transformMatrix * vertex.position;
	}
}

void Shape::merge(const Shape& shape)
{
	if (this->drawMode != shape.drawMode) {
		throw std::invalid_argument("Only shapes with the same draw mode can be merged");
	}

	unsigned addedIndicesOffset = vertices.size();

	for (const VertexFormat& vertex : shape.vertices) {
		vertices.push_back(vertex);
	}

	for (unsigned index : shape.indices) {
		indices.push_back(addedIndicesOffset + index);
	}
}

Mesh* Shape::convertToMesh(const std::string& name) const
{
	Mesh* mesh = new Mesh(name);

	mesh->SetDrawMode(drawMode);
	mesh->InitFromData(vertices, indices);

	return mesh;
}

