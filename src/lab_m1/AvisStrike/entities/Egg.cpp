#include "Egg.h"
#include "../Constants.h"

Egg::Egg(glm::vec2 speed)
	: Entity(
		"egg", 
		2.f * EGG_X_RADIUS,
		2.f * EGG_Y_RADIUS,
		EntityHitboxShape::RECTANGLE
	),
	speed(speed)
{
	shouldDespawn = false;
}

void Egg::update(float deltaTimeSeconds)
{
	move(speed * deltaTimeSeconds);

	if (position.y < -EGG_Y_RADIUS) {
		shouldDespawn = true;
	}
}

bool Egg::hasDespawned() const
{
	return shouldDespawn;
}

void Egg::despawn()
{
	shouldDespawn = true;
}
