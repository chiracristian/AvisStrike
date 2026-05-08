#include "SolidBlockShape.h"
#include "ShapeFactory.h"
#include "../transform2D.h"

constexpr float SOLID_BLOCK_LENGTH = TILE_LENGTH;

constexpr glm::vec3 CENTER_COLOR = { 1.f, 1.f, 1.f };
constexpr glm::vec3 EDGE_COLOR = { 0.6f, 0.6f, 0.6f };

SolidBlockShape::SolidBlockShape(unsigned drawMode)
{
	glm::vec2 center = { 0.f, 0.f };

	glm::vec2 bottomLeftCorner = {
		-SOLID_BLOCK_LENGTH / 2.f,
		-SOLID_BLOCK_LENGTH / 2.f 
	};

	glm::vec2 bottomRightC = {
		SOLID_BLOCK_LENGTH / 2.f,
		-SOLID_BLOCK_LENGTH / 2.f 
	};

	glm::vec2 topRightCorner = { 
		SOLID_BLOCK_LENGTH / 2.f, 
		SOLID_BLOCK_LENGTH / 2.f 
	};

	glm::vec2 topLeftC = {
		-SOLID_BLOCK_LENGTH / 2.f, 
		SOLID_BLOCK_LENGTH / 2.f 
	};
	
	Shape bottomTriangle = ShapeFactory::triangle(
		bottomLeftCorner,
		bottomRightC,
		center,
		EDGE_COLOR,
		EDGE_COLOR,
		CENTER_COLOR);

	Shape rightTriangle = ShapeFactory::triangle(
		bottomRightC,
		topRightCorner,
		center,
		EDGE_COLOR,
		EDGE_COLOR,
		CENTER_COLOR);

	Shape topTriangle = ShapeFactory::triangle(
		topRightCorner,
		topLeftC,
		center,
		EDGE_COLOR,
		EDGE_COLOR,
		CENTER_COLOR);

	Shape leftTriangle = ShapeFactory::triangle(
		topLeftC,
		bottomLeftCorner,
		center,
		EDGE_COLOR,
		EDGE_COLOR,
		CENTER_COLOR);

	this->merge(leftTriangle);
	this->merge(rightTriangle);
	this->merge(topTriangle);
	this->merge(bottomTriangle);
}
