#include "StartButtonShape.h"

#include "ShapeFactory.h"
#include "../Constants.h"

StartButtonShape::StartButtonShape(glm::vec3 color, unsigned drawMode)
{
	glm::vec2 bottomLeftCorner = {
		-AVAILABLE_BLOCK_LENGTH / 2.f,
		-AVAILABLE_BLOCK_LENGTH / 2.f
	};

	glm::vec2 bottomRightCorner = {
		AVAILABLE_BLOCK_LENGTH / 2.f,
		-AVAILABLE_BLOCK_LENGTH / 2.f
	};

	glm::vec2 topRightCorner = {
		AVAILABLE_BLOCK_LENGTH / 2.f,
		AVAILABLE_BLOCK_LENGTH / 2.f
	};

	glm::vec2 topLeftCorner = {
		-AVAILABLE_BLOCK_LENGTH / 2.f,
		AVAILABLE_BLOCK_LENGTH / 2.f
	};

	Shape lowerTriangle = ShapeFactory::triangle(
		bottomLeftCorner,
		bottomRightCorner,
		topLeftCorner,
		color
	);

	Shape upperTriangle = ShapeFactory::triangle(
		bottomLeftCorner,
		topRightCorner,
		topLeftCorner,
		color
	);

	this->merge(lowerTriangle);
	this->merge(upperTriangle);
}
