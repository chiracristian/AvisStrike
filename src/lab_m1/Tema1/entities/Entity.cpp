#include "Entity.h"

#include "../transform2D.h"

const std::string& Entity::getMeshName() const
{
	return meshName;
}

glm::vec2 Entity::getPosition() const
{
	return position;
}

void Entity::setPosition(glm::vec2 position)
{
	this->position = position;
	modelMatrix = transf2D::translate(position.x, position.y);
}

void Entity::move(glm::vec2 amount)
{
	setPosition(position + amount);
}

const glm::mat3& Entity::getModelMatrix() const
{
	return modelMatrix;
}

static float clamp(float value, float minimum, float maximum)
{
	if (value < minimum) {
		return minimum;
	}
	if (value > maximum) {
		return maximum;
	}
	return value;
}

bool Entity::collide(const Entity& e1, const Entity& e2)
{
	// Rectangle vs Rectangle
	if (e1.hitboxShape == EntityHitboxShape::RECTANGLE &&
		e2.hitboxShape == EntityHitboxShape::RECTANGLE)
	{
		glm::vec2 posDiff = e1.position - e2.position;

		return std::abs(posDiff.y) <= (e1.height + e2.height) / 2.f &&
			std::abs(posDiff.x) <= (e1.width + e2.width) / 2.f;
	}

	// Circle vs Cirlce
	if (e1.hitboxShape == EntityHitboxShape::CIRCLE &&
		e2.hitboxShape == EntityHitboxShape::CIRCLE)
	{
		glm::vec2 squarePosDiff = e1.position - e2.position;
		squarePosDiff.x *= squarePosDiff.x;
		squarePosDiff.y *= squarePosDiff.y;

		float radius1 = e1.radius / 2.f;
		float radius2 = e2.radius / 2.f;

		float radiusSquareSum = radius1 + radius2;
		radiusSquareSum *= radiusSquareSum;

		return squarePosDiff.x + squarePosDiff.y <= radiusSquareSum;
	}

	// Circle vs Rectangle
	if (e1.hitboxShape == EntityHitboxShape::CIRCLE &&
		e2.hitboxShape == EntityHitboxShape::RECTANGLE)
	{
		glm::vec2 posDiff = e1.position - e2.position;
		float halfWidth = e2.width / 2.f;
		float halfHeight = e2.height / 2.f;

		glm::vec2 closest = {
			clamp(posDiff.x, -halfWidth, halfWidth),
			clamp(posDiff.y, -halfHeight, halfHeight)
		};

		glm::vec2 dist = posDiff - closest;

		return dist.x * dist.x + dist.y * dist.y <= e1.radius * e1.radius;
	}

	// Rectangle vs Circle
	if (e1.hitboxShape == EntityHitboxShape::RECTANGLE &&
		e2.hitboxShape == EntityHitboxShape::CIRCLE)
	{
		glm::vec2 posDiff = e1.position - e2.position;
		float halfWidth = e1.width / 2.f;
		float halfHeight = e1.height / 2.f;

		glm::vec2 closest = {
			clamp(posDiff.x, -halfWidth, halfWidth),
			clamp(posDiff.y, -halfHeight, halfHeight)
		};

		glm::vec2 dist = posDiff - closest;

		return dist.x * dist.x + dist.y * dist.y <= e2.radius * e2.radius;
	}

	return false;
}

Entity::Entity(
	const std::string& meshName, 
	float width,
	float height, 
	EntityHitboxShape hitboxShape)
	: meshName(meshName), width(width), height(height), hitboxShape(hitboxShape)
{
	setPosition(glm::vec2(0.f, 0.f));
}
