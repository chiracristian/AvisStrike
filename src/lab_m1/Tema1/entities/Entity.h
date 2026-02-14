#pragma once

#include <string>
#include <glm/vec2.hpp>
#include <glm/mat3x3.hpp>

enum class EntityHitboxShape {
	RECTANGLE,
	CIRCLE
};


class Entity
{
public:
	const std::string& getMeshName() const;

	glm::vec2 getPosition() const;
	void setPosition(glm::vec2 position);
	void move(glm::vec2 amount);

	const glm::mat3& getModelMatrix() const;

	virtual void update(float deltaTimeSeconds) = 0;

	static bool collide(const Entity& e1, const Entity& e2);

	virtual ~Entity() = default;
protected:
	Entity(
		const std::string& meshName, 
		float width, 
		float height,
		EntityHitboxShape hitboxShape
	);

	std::string meshName;
	union {
		float width;
		float radius;
	};
	float height;
	EntityHitboxShape hitboxShape;

	glm::mat3 modelMatrix;
	glm::vec2 position;
};