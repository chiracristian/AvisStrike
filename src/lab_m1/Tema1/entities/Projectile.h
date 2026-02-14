#pragma once

#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(glm::vec2 speed);
	void update(float deltaTimeSeconds) override;

	bool hasDespawned() const;
	void despawn();
private:
	glm::vec2 speed;
	bool shouldDespawn;
};