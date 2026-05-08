#include "ShapeFactory.h"
#include <stdexcept>

Shape ShapeFactory::rectangle(float width, float height, glm::vec3 color)
{
	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-width / 2.f, -height / 2.f, 1.f), // 0 - bottom-left
			color,
			NORMAL
		),
		VertexFormat(glm::vec3(width / 2.f, -height / 2.f, 1.f), // 1 - bottom-right
			color,
			NORMAL
		),
		VertexFormat(glm::vec3(width / 2.f,  height / 2.f, 1.f), // 2 - top-right
			color,
			NORMAL
		),
		VertexFormat(glm::vec3(-width / 2.f,  height / 2.f, 1.f), // 3 - top-left
			color,
			NORMAL
		)
	};

	std::vector<unsigned> indices = {
		0, 1, 2, // bottom-right triangle
		0, 2, 3  // top-left triangle
	};

	return Shape(vertices, indices);
}

Shape ShapeFactory::rectangleOutline(float width, float height, glm::vec3 color)
{
	std::vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-width / 2.f, -height / 2.f, 1.f), // 0 - bottom-left
			color, 
			NORMAL
		), 
		VertexFormat(glm::vec3( width / 2.f, -height / 2.f, 1.f), // 1 - bottom-right
			color, 
			NORMAL
		), 
		VertexFormat(glm::vec3( width / 2.f,  height / 2.f, 1.f), // 2 - top-right
			color,
			NORMAL
		), 
		VertexFormat(glm::vec3(-width / 2.f,  height / 2.f, 1.f), // 3 - top-left
			color, 
			NORMAL
		)
	};

	std::vector<unsigned> indices = {
		0, 1, // bottom side
		1, 2, // right side
		2, 3, // top side
		3, 0  // left side
	};

	return Shape(vertices, indices, GL_LINES);
}

Shape ShapeFactory::square(float length, glm::vec3 color)
{
	return rectangle(length, length, color);
}

Shape ShapeFactory::ellipse(
	float x_radius, 
	float y_radius,
	glm::vec3 color, 
	unsigned vertexCount)
{
	if (vertexCount < 3) {
		throw std::invalid_argument(
			"At least 3 edges are required for an ellipse approximation"
		);
	}

	float period = 2.f * M_PI;
	std::vector<float> theta_values;
	theta_values.reserve(vertexCount);

	for (int i = 0; i < vertexCount; i++) {
		theta_values.push_back(i * period / vertexCount);
	}

	// Add the vertices
	std::vector<VertexFormat> vertices;
	vertices.reserve(1 + vertexCount);
	
	// Add the center point
	vertices.emplace_back(glm::vec3(0.f, 0.f, 1.f), color, NORMAL);
	for (int i = 0; i < vertexCount; i++) {
		float x = x_radius * std::cos(theta_values[i]);
		float y = y_radius * std::sin(theta_values[i]);

		// Add the points at regular intervals
		vertices.emplace_back(glm::vec3(x, y, 1.f), color, NORMAL);
	}

	// Add the indices of the triangles
	std::vector<unsigned> indices;
	indices.reserve(3 * vertexCount);
	for (int i = 1; i < vertexCount; i++) {
		indices.push_back(0); // put the center
		indices.push_back(i); // put the current point
		indices.push_back(i + 1); // put the next point
	}
	// put the last triangle
	indices.push_back(0);
	indices.push_back(vertexCount);
	indices.push_back(1);

	return Shape(vertices, indices);
}

Shape ShapeFactory::circle(float radius, glm::vec3 color, unsigned vertexCount)
{
	return ellipse(radius, radius, color, vertexCount);
}

Shape ShapeFactory::triangle(
	glm::vec2 corner1_pos, 
	glm::vec2 corner2_pos, 
	glm::vec2 corner3_pos, 
	glm::vec3 color)
{
	return triangle(corner1_pos, corner2_pos, corner3_pos, color, color, color);
}

Shape ShapeFactory::triangle(
	glm::vec2 corner1_pos, 
	glm::vec2 corner2_pos,
	glm::vec2 corner3_pos,
	glm::vec3 corner1_color, 
	glm::vec3 corner2_color,
	glm::vec3 corner3_color)
{
	std::vector<VertexFormat> vertices = {
		VertexFormat(
			glm::vec3(corner1_pos.x, corner1_pos.y, 1.f),
			corner1_color, 
			NORMAL
		),
		VertexFormat(glm::vec3(corner2_pos.x, corner2_pos.y, 1.f), 
			corner2_color,
			NORMAL
		),
		VertexFormat(glm::vec3(corner3_pos.x, corner3_pos.y, 1.f), 
			corner3_color,
			NORMAL
		),
	};
	std::vector<unsigned> indices = { 0, 1, 2 };

	return Shape(vertices, indices);
}

