#include "Chicken.h"
#include "../shapes/ChickenShape.h"
#include "../Constants.h"

constexpr float FIRE_PERIOD_BASE = 2.2f;
constexpr float FIRE_PERIOD_PER_WAVE = 0.2f;
constexpr float FIRE_PERIOD_MIN = 0.05f;

constexpr float FIRE_PROB_BASE = 0.1f;
constexpr float FIRE_PROB_PER_WAVE = 0.1f;

constexpr float FIRE_JITTER_BASE = 0.1f;
constexpr float FIRE_JITTER_PER_WAVE = 0.05f;
constexpr float FIRE_JITTER_MAX = 0.8f;

constexpr float OSC_FREQ_BASE = 0.04f;
constexpr float OSC_FREQ_PER_WAVE = 0.02f;
constexpr float OSC_FREQ_MAX = 0.2f;

constexpr float DOWN_SPEED_BASE = 2.5f;
constexpr float DOWN_SPEED_PER_WAVE = 2.5f;

constexpr glm::vec2 EGG_SPEED_BASE = { 0.f, -50.f };
constexpr glm::vec2 EGG_SPEED_PER_WAVE = { 0.f, -50.f };

constexpr float ENTRANCE_ANIMATION_TIME = 0.5f;

ChickenProperties::ChickenProperties(int wave)
{
	eggSpeed = EGG_SPEED_BASE + EGG_SPEED_PER_WAVE * (float)wave;

	firePeriod = std::max(FIRE_PERIOD_BASE - wave * FIRE_PERIOD_PER_WAVE, FIRE_PERIOD_MIN);
	fireProbability = FIRE_PROB_BASE + wave * FIRE_PROB_PER_WAVE;
	fireJitter = std::min(FIRE_JITTER_BASE + wave * FIRE_JITTER_PER_WAVE, FIRE_JITTER_MAX);

	oscillationFrequency = std::min(OSC_FREQ_BASE + wave * OSC_FREQ_PER_WAVE, OSC_FREQ_MAX);
	downwardsSpeed = DOWN_SPEED_BASE + wave * DOWN_SPEED_PER_WAVE;
}

Chicken::Chicken(
	glm::vec2 initialPosition,
	const ChickenProperties& properties,
	bool reversePhase)
	: Entity(
		"chicken", 
		ChickenShape::getWidth() / 2.f,
		ChickenShape::getHeight() / 2.f,
		EntityHitboxShape::CIRCLE
	),
	initialPosition(initialPosition),
	properties(properties),
	reversePhase(reversePhase)
{
	setPosition(initialPosition);

	dead = false;
	dueToFire = false;
	fireTimer = 0.f;
	oscillationTimer = 0.f;

	entranceAnimation = true;
	entranceAnimationTimer = 0.f;
	entranceAnimationSpeed = 2.f * ChickenShape::getHeight() / ENTRANCE_ANIMATION_TIME;
}

void Chicken::update(float deltaTimeSeconds)
{
	if (entranceAnimation) {
		entranceAnimationTimer += deltaTimeSeconds;
		move(glm::vec2(0.f, -entranceAnimationSpeed * deltaTimeSeconds));

		if (entranceAnimationTimer >= ENTRANCE_ANIMATION_TIME) {
			entranceAnimation = false;
		}
		return;
	}
	// Process oscillations
	oscillationTimer += deltaTimeSeconds;
	float pulsation = 2.f * M_PI * properties.oscillationFrequency;
	if (oscillationTimer >= 2.f * M_PI / pulsation) {
		oscillationTimer -= 2.f * M_PI / pulsation;
	}

	float currentPhase = pulsation * oscillationTimer;
	if (reversePhase) {
		currentPhase += M_PI;
	}

	float amplitude = 2.f * ChickenShape::getWidth();
	float xPos = initialPosition.x + amplitude * std::sin(currentPhase);

	// Move downwards
	float yPos = position.y - properties.downwardsSpeed * deltaTimeSeconds;
	setPosition(glm::vec2(xPos, yPos));

	// Process firing
	fireTimer += deltaTimeSeconds;
	
	if (fireTimer >= properties.firePeriod) {
		fireTimer = (float)rand()* properties.fireJitter * properties.firePeriod / RAND_MAX;
		if ((float)rand() / RAND_MAX <= properties.fireProbability) {
			dueToFire = true;
		}
	}
}

glm::vec2 Chicken::getEggSpeed() const
{
	return properties.eggSpeed;
}

bool Chicken::fireIfDue()
{
	if (dueToFire) {
		dueToFire = false;
		return true;
	}
	return false;
}

bool Chicken::isDead() const
{
	return dead;
}

void Chicken::kill()
{
	// During the entrance animation, the chicken are invulnerable
	if (!entranceAnimation)
		dead = true;
}
