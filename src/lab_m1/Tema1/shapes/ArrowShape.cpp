#include "ArrowShape.h"

#include "ShapeFactory.h"
#include "../Constants.h"
#include "../transform2D.h"

ArrowShape::ArrowShape(
	float width, 
	float height, 
	float tipWidth,
	float tipHeight,
	glm::vec3 color, 
	unsigned drawMode)
{
	Shape triangle = ShapeFactory::triangle(
		glm::vec2(-tipWidth / 2.f, 0.f),
		glm::vec2(tipWidth / 2.f, 0.f),
		glm::vec2(0.f, tipHeight),
		color
	);
	triangle.applyTransform(transf2D::translate(0.f, height / 2.f));

	Shape rectangle = ShapeFactory::rectangle(width, height, color);

	this->merge(triangle);
	this->merge(rectangle);
}
