#pragma once

#include "Shape.h"

class StartButtonShape : public Shape
{
public:
	StartButtonShape(glm::vec3 color, unsigned drawMode = GL_TRIANGLES);
};