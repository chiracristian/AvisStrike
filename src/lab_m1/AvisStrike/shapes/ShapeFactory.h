#pragma once

#include "Shape.h"
#include "../Constants.h"

class ShapeFactory 
{
public:
	static Shape rectangle(float width, float height, glm::vec3 color );
	static Shape rectangleOutline(float width, float height, glm::vec3 color);
	static Shape square(float length, glm::vec3 color);

	static Shape ellipse(float x_radius, float y_radius, glm::vec3 color, unsigned vertexCount = CIRCLE_EDGE_COUNT);
	static Shape circle(float radius, glm::vec3 color, unsigned vertexCount = CIRCLE_EDGE_COUNT);

	static Shape triangle(glm::vec2 corner1_pos, glm::vec2 corner2_pos, glm::vec2 corner3_pos, glm::vec3 color);
	static Shape triangle(glm::vec2 corner1_pos, glm::vec2 corner2_pos, glm::vec2 corner3_pos, 
		glm::vec3 corner1_color, glm::vec3 corner2_color, glm::vec3 corner3_color);
private:
	ShapeFactory();
};
