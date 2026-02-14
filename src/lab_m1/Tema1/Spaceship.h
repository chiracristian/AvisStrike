#pragma once

#include "entities/Entity.h"
#include "SpaceshipData.h"
#include "entities/SolidBlock.h"
#include "entities/Turret.h"
#include "entities/EngineBlock.h"

class Spaceship
{
public:
	Spaceship(
		const SpaceshipData& data,
		glm::vec2 initialPos,
		int engineLevel,
		int turretLevel
	);
	void move(glm::vec2 direction, float deltaTime);
	bool collide(const Entity& e);
	void update(float deltaTimeSeconds);

	const std::vector<std::shared_ptr<Entity>>& getEntities() const;
	const std::vector<std::shared_ptr<Turret>>& getTurrets() const;
	float getWidth() const;
	float getHeight() const;
	glm::vec2 getPosition() const;

private:
	std::vector<std::shared_ptr<Entity>> entities;
	std::vector<std::shared_ptr<Turret>> turrets;
	float width;
	float height;
	float speed;
	glm::vec2 position;
};