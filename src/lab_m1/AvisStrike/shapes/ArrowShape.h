#pragma once

#include "Shape.h"

class ArrowShape : public Shape
{
public:
	ArrowShape(
		float width,
		float height,
		float tipWidth,
		float tipHeight,
		glm::vec3 color, 
		unsigned drawMode = GL_TRIANGLES
	);
};