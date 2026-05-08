#include "Spaceship.h"
#include "Constants.h"

Spaceship::Spaceship(
	const SpaceshipData& data, 
	glm::vec2 initialPos,
	int engineLevel,
	int turretLevel)
{
	Array2DPos topLeftC = data.getTopLeftCorner();
	Array2DPos bottomRightC = data.getBottomRightCorner();

	width = (bottomRightC.col - topLeftC.col + 1) * TILE_LENGTH;
	height = (bottomRightC.row - topLeftC.row + 1) * TILE_LENGTH;
	speed = SPACESHIP_ENGINE_SPEED_PER_LEVEL * engineLevel * data.getEngineCount();

	float firePeriod = std::max(
		TURRET_FIRE_PERIOD_MIN,
		TURRET_FIRE_PERIOD_BASE - turretLevel * TURRET_FIRE_PERIOD_PER_LEVEL
	);

	// Put entities in the corresponding positions
	for (size_t row = topLeftC.row; row < bottomRightC.row + 1; row++) {
		for (size_t col = topLeftC.col; col < bottomRightC.col + 1; col++) {
			switch (data.getBlockAt(row, col)) {
			case SpaceshipBlock::SOLID:
			{
				entities.emplace_back(std::make_shared<SolidBlock>());
				break;
			}

			case SpaceshipBlock::TURRET:
			{
				std::shared_ptr<Turret> newTurret = 
					std::make_shared<Turret>(firePeriod);
				entities.push_back(newTurret);
				turrets.push_back(newTurret);
				break;
			}

			case SpaceshipBlock::ENGINE:
			{
				entities.emplace_back(std::make_shared<EngineBlock>());
				break;
			}
				
			default:
				continue;
			}

			glm::vec2 bottomLeftPos = {
				(col - topLeftC.col + 0.5f) * TILE_LENGTH,
				(bottomRightC.row - row + 0.5f) * TILE_LENGTH
			};
			
			glm::vec2 centerPos = {
				bottomLeftPos.x + initialPos.x - width / 2.f,
				bottomLeftPos.y + initialPos.y - height / 2.f
			};

			entities.back()->setPosition(centerPos);
		}
	}

	position = initialPos;
}

void Spaceship::move(glm::vec2 direction, float deltaTime)
{
	glm::vec2 amount = direction * deltaTime * speed;
	position += amount;
	for (auto& entity : entities) {
		entity->move(amount);
	}
}

bool Spaceship::collide(const Entity& e)
{
	for (const auto& entity : entities) {
		if (Entity::collide(*entity, e)) {
			return true;
		}
	}
	return false;
}

void Spaceship::update(float deltaTimeSeconds)
{
	// Update the turrets
	for (const auto& turret : turrets) {
		turret->update(deltaTimeSeconds);
	}
}

const std::vector<std::shared_ptr<Entity>>& Spaceship::getEntities() const
{
	return entities;
}

const std::vector<std::shared_ptr<Turret>>& Spaceship::getTurrets() const
{
	return turrets;
}

float Spaceship::getWidth() const
{
	return width;
}

float Spaceship::getHeight() const
{
	return height;
}

glm::vec2 Spaceship::getPosition() const
{
	return position;
}
