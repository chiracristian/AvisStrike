#pragma once

#include "Shape.h"

class ChickenShape : public Shape
{
public:
	ChickenShape(unsigned drawMode = GL_TRIANGLES);

	static float getWidth();
	static float getHeight();
};