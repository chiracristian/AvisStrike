#include "TurretShape.h"
#include "ShapeFactory.h"
#include "../transform2D.h"

constexpr float BASE_SQUARE_WIDTH = TILE_LENGTH;
constexpr float BASE_SQUARE_HEIGHT = TILE_LENGTH / 2.f;

constexpr float BASE_CIRCLE_RADIUS = TILE_LENGTH / 2.f;

constexpr float BARREL_WIDTH = 0.75f * TILE_LENGTH;
constexpr float BARREL_HEIGHT = 3.f * TILE_LENGTH;

constexpr float BARREL_TIP_WIDTH = TILE_LENGTH;
constexpr float BARREL_TIP_HEIGHT = 0.1f * TILE_LENGTH;

constexpr glm::vec3 BASE_SQUARE_COLOR = glm::vec3(0.85f, 0.85f, 0.85f);
constexpr glm::vec3 BASE_CIRCLE_COLOR = glm::vec3(0.55f, 0.55f, 0.55f);
constexpr glm::vec3 BARREL_COLOR = glm::vec3(0.2f, 0.2f, 0.2f);
constexpr glm::vec3 BARREL_TIP_COLOR = glm::vec3(0.3f, 0.3f, 0.3f);

TurretShape::TurretShape(unsigned drawMode)
{
	Shape baseCircle = ShapeFactory::circle(BASE_CIRCLE_RADIUS, BASE_CIRCLE_COLOR);

	Shape baseRectangle = ShapeFactory::rectangle(BASE_SQUARE_WIDTH, BASE_SQUARE_HEIGHT, BASE_SQUARE_COLOR);
	baseRectangle.applyTransform(transf2D::translate(0.f, -BASE_SQUARE_HEIGHT / 2.f));

	Shape barrel = ShapeFactory::rectangle(BARREL_WIDTH, BARREL_HEIGHT, BARREL_COLOR);
	barrel.applyTransform(transf2D::translate(0.f, TILE_LENGTH));

	Shape barrelTip = ShapeFactory::rectangle(BARREL_TIP_WIDTH, BARREL_TIP_HEIGHT, BARREL_TIP_COLOR);
	barrelTip.applyTransform(transf2D::translate(0.f, 2.5f * TILE_LENGTH));

	this->merge(baseRectangle);
	this->merge(baseCircle);
	this->merge(barrelTip);
	this->merge(barrel);
}