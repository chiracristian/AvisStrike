#pragma once

#include "Entity.h"

struct ChickenProperties
{
	glm::vec2 eggSpeed;
	float firePeriod;
	float fireProbability;
	float fireJitter;
	float oscillationFrequency;
	float downwardsSpeed;

	// Construct properties based on wave
	ChickenProperties(int wave);
};

class Chicken : public Entity
{
public:
	Chicken(
		glm::vec2 initialPosition,
		const ChickenProperties& properties,
		bool reversePhase
	);
	void update(float deltaTimeSeconds) override;

	glm::vec2 getEggSpeed() const;
	bool fireIfDue();
	bool isDead() const;
	void kill();
private:
	ChickenProperties properties;
	glm::vec2 initialPosition;
	bool dead;

	bool dueToFire;
	float fireTimer;

	float oscillationTimer;
	bool reversePhase;

	bool entranceAnimation;
	float entranceAnimationTimer;
	float entranceAnimationDistance;
	float entranceAnimationSpeed;
};