#include "SolidBlock.h"
#include "../Constants.h"

SolidBlock::SolidBlock()
	: Entity(
		"solid_block",
		TILE_LENGTH,
		TILE_LENGTH,
		EntityHitboxShape::RECTANGLE
	)
{

}

void SolidBlock::update(float deltaTimeSeconds)
{

}
