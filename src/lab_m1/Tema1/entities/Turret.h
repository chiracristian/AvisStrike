#pragma once

#include "Entity.h"

class Turret : public Entity
{
public:
	Turret(float firePeriod);
	void update(float deltaTimeSeconds) override;

	bool fireIfAble();
private:
	float fireTimer;
	float firePeriod;
	bool canFire;
};