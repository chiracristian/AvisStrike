#include "Turret.h"
#include "../Constants.h"

Turret::Turret(float firePeriod)
	: Entity(
		"turret",
		TILE_LENGTH,
		3.f * TILE_LENGTH,
		EntityHitboxShape::RECTANGLE
	), firePeriod(firePeriod)
{
	fireTimer = 0.f;
	canFire = false;
}

void Turret::update(float deltaTimeSeconds)
{
	fireTimer += deltaTimeSeconds;
	if (fireTimer >= firePeriod) {
		canFire = true;
	}
}

bool Turret::fireIfAble()
{
	if (canFire) {
		canFire = false;
		fireTimer = 0.f;
		return true;
	}
	return false;
}

