#include "EngineBlock.h"
#include "../Constants.h"

EngineBlock::EngineBlock()
	: Entity(
		"engine",
		TILE_LENGTH,
		TILE_LENGTH,
		EntityHitboxShape::RECTANGLE
	)
{

}

void EngineBlock::update(float deltaTimeSeconds)
{

}
