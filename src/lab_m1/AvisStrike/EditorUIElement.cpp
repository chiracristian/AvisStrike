#include "EditorUIElement.h"
#include "transform2D.h"

EditorUIElement::EditorUIElement()
{
}

EditorUIElement::EditorUIElement(
	const std::string& meshName,
	float width,
	float height,
	float Scale
	)
	: meshName(meshName), width(width * Scale), height(height * Scale), Scale(Scale)
{
	setPosition(glm::vec2(0.f, 0.f));
}

const std::string& EditorUIElement::getMeshName() const
{
	return meshName;
}

glm::vec2 EditorUIElement::getPosition() const
{
	return position;
}

void EditorUIElement::setPosition(glm::vec2 position)
{
	this->position = position;
	modelMatrix = transf2D::translate(position.x, position.y) * transf2D::scale(Scale, Scale);;
}

const glm::mat3& EditorUIElement::getModelMatrix() const
{
	return modelMatrix;
}

bool EditorUIElement::pointIsContained(glm::vec2 point) const
{
	glm::vec2 posDiff = point - position;
	return std::abs(posDiff.x) <= width / 2.f && std::abs(posDiff.y) <= height / 2.f;
}
