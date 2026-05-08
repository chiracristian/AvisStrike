#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

class EditorUIElement
{
public:
	EditorUIElement();
	EditorUIElement(const std::string& meshName, float width, float height, float Scale = 1.f);
	const std::string& getMeshName() const;

	glm::vec2 getPosition() const;
	void setPosition(glm::vec2 position);
	const glm::mat3& getModelMatrix() const;

	bool pointIsContained(glm::vec2 point) const;

private:
	std::string meshName;
	float width;
	float height;
	float Scale;
	glm::mat3 modelMatrix;
	glm::vec2 position;
};