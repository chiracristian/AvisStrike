#pragma once

#include "Entity.h"

class Egg : public Entity
{
public:
	Egg(glm::vec2 speed);
	void update(float deltaTimeSeconds) override;

	bool hasDespawned() const;
	void despawn();
private:
	glm::vec2 speed;
	bool shouldDespawn;
};