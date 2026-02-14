#pragma once

#include "Array2D.h"

#include <algorithm>
#include <memory>
#include "shapes/Shape.h"

#include "entities/Entity.h"

enum class SpaceshipBlock {
	NONE = -1,
	OCCUPIED = -2,
	SOLID = 0,
	ENGINE = 1,
	TURRET = 2,
};

class SpaceshipData
{
public:
	SpaceshipData();

	bool addBlock(size_t row, size_t col, SpaceshipBlock type);
	bool removeBlock(size_t row, size_t col);

	SpaceshipBlock getBlockAt(size_t row, size_t col) const;

	bool isValid() const;
	size_t getAvailableBlocks() const;
	Array2DPos getTopLeftCorner() const;
	Array2DPos getBottomRightCorner() const;
	size_t getEngineCount() const;
	
private:
	Array2D<SpaceshipBlock> blocks;
	
	size_t availableBlocks;
	std::vector<Array2DPos> turrets;
	std::vector<Array2DPos> engines;

	bool isConex() const;
};