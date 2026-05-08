#pragma once

#include "Shape.h"

class SolidBlockShape : public Shape
{
public:
	SolidBlockShape(unsigned drawMode = GL_TRIANGLES);
};