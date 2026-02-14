#include "Projectile.h"
#include "../Constants.h"

Projectile::Projectile(glm::vec2 speed)
	: Entity(
		"projectile", 
		PROJECTILE_RADIUS,
		PROJECTILE_RADIUS,
		EntityHitboxShape::CIRCLE
	),
	speed(speed)
{
	shouldDespawn = false;
}

void Projectile::update(float deltaTimeSeconds)
{
	move(speed * deltaTimeSeconds);

	if (position.y > SCREEN_HEIGHT + PROJECTILE_RADIUS) {
		shouldDespawn = true;
	}
}

bool Projectile::hasDespawned() const
{
	return shouldDespawn;
}

void Projectile::despawn()
{
	shouldDespawn = true;
}
