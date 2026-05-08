#include "SpaceshipData.h"

#include <stack>

#include "Constants.h"
#include "transform2D.h"

SpaceshipData::SpaceshipData()
	: blocks(SPACESHIP_GRID_ROWS, SPACESHIP_GRID_COLS, SpaceshipBlock::NONE)
{
	availableBlocks = MAX_SPACESHIP_BLOCKS;
}

bool SpaceshipData::addBlock(size_t row, size_t col, SpaceshipBlock type)
{
	// Do not add a block if we have no more blocks to add
	if (availableBlocks == 0) {
		return false;
	}

	// Or if the space is already occupied
	if (blocks.at(row, col) != SpaceshipBlock::NONE) {
		return false;
	}

	// Add special blocks in their corresponding arrays
	switch (type) {
	case SpaceshipBlock::TURRET:
		if (row < 2) {
			return false;
		}
		turrets.emplace_back(row, col);
		blocks.at(row - 1, col) = SpaceshipBlock::OCCUPIED;
		blocks.at(row - 2, col) = SpaceshipBlock::OCCUPIED;
		break;

	case SpaceshipBlock::ENGINE:
		engines.emplace_back(row, col);
		break;

	default:
		break;
	}
	
	// Put the block in the array and decrease available blocks
	blocks.at(row, col) = type;
	availableBlocks--;

	return true;
}

bool SpaceshipData::removeBlock(size_t row, size_t col)
{
	Array2DPos pos = { row, col };

	// Do nothing if trying to remove from an empty space
	switch (blocks.at(row, col)) {
	case SpaceshipBlock::NONE:
		return false;
		
	// If it's a turret, remove it from the list of them
	case SpaceshipBlock::TURRET:
		for (size_t i = 0; i < turrets.size(); i++) {
			if (turrets[i] == pos) {
				turrets[i] = turrets.back();
				turrets.pop_back();

				blocks.at(row - 1, col) = SpaceshipBlock::NONE;
				blocks.at(row - 2, col) = SpaceshipBlock::NONE;
				break;
			}
		}
		break;

	// Same for an engine
	case SpaceshipBlock::ENGINE:
		for (size_t i = 0; i < engines.size(); i++) {
			if (engines[i] == pos) {
				engines[i] = engines.back();
				engines.pop_back();
				break;
			}
		}
		break;

	default:
		break;
	}
	blocks.at(row, col) = SpaceshipBlock::NONE;

	// Increase the number of available blocks
	availableBlocks++;
	return true;
}

SpaceshipBlock SpaceshipData::getBlockAt(size_t row, size_t col) const
{
	return blocks.at(row, col);
}

bool SpaceshipData::isValid() const
{
	// Check if there is any block above a turret
	for (int i = 0; i < turrets.size(); i++) {
		Array2DPos pos = turrets[i];
		for (size_t row = pos.row - 1; row-- > 0; ) {
			if (blocks.at(row, pos.col) != SpaceshipBlock::NONE &&
				blocks.at(row, pos.col) != SpaceshipBlock::OCCUPIED) {
				return false;
			}
		}
	}

	// Check if there is a block under an engine
	for (int i = 0; i < engines.size(); i++) {
		Array2DPos pos = engines[i];
		for (size_t row = pos.row + 1; row < SPACESHIP_GRID_ROWS; row++) {
			if (blocks.at(row, pos.col) != SpaceshipBlock::NONE &&
				blocks.at(row, pos.col) != SpaceshipBlock::OCCUPIED) {
				return false;
			}
		}
	}

	// The vehicle must also be conex
	return isConex();
}

size_t SpaceshipData::getAvailableBlocks() const
{
	return availableBlocks;
}

bool SpaceshipData::isConex() const
{
	// The vehicle must have at least one engine and one turret
	if (turrets.size() == 0 || engines.size() == 0)
		return false;

	// Create a visited matrix
	Array2D<int> visited(SPACESHIP_GRID_ROWS, SPACESHIP_GRID_COLS, 0);

	// Perform a DFS starting from the first engine
	Array2DPos startPos = engines[0];

	std::stack<Array2DPos> stack;
	stack.push(startPos);
	visited.at(startPos) = true;

	while (!stack.empty()) {
		Array2DPos currentPos = stack.top();
		stack.pop();

		for (Direction d : DIRECTIONS) {
			if (currentPos.canStep(d, SPACESHIP_GRID_ROWS, SPACESHIP_GRID_COLS)) {
				Array2DPos nextPos = currentPos.step(d);
				if (blocks.at(nextPos) != SpaceshipBlock::NONE &&
					!visited.at(nextPos)) {
					visited.at(nextPos) = true;
					stack.push(nextPos);
				}
			}
		}
	}

	// If any non-visited cell is found, the vehicle is not conex
	for (size_t i = 0; i < SPACESHIP_GRID_ROWS; i++) {
		for (size_t j = 0; j < SPACESHIP_GRID_COLS; j++) {
			if (blocks.at(i, j) != SpaceshipBlock::NONE &&
				!visited.at(i, j)) {
				return false;
			}
		}
	}

	return true;
}

Array2DPos SpaceshipData::getTopLeftCorner() const
{
	Array2DPos result;

	bool foundTop = false;
	result.col = SPACESHIP_GRID_COLS - 1;

	// Find the top left corner of the region that has non-empty blocks
	for (size_t row = 0; row < SPACESHIP_GRID_ROWS; row++) {
		for (size_t col = 0; col < SPACESHIP_GRID_COLS; col++) {
			if (blocks.at(row, col) != SpaceshipBlock::NONE) {
				if (!foundTop) {
					result.row = row;
					foundTop = true;
				}

				result.col = std::min(col, result.col);
				break;
			}
		}
	}
	return result;
}

Array2DPos SpaceshipData::getBottomRightCorner() const
{
	Array2DPos result;

	bool foundBottom = false;
	result.col = 0;

	// Find the bottom right corner of the region that has non-empty blocks
	for (size_t row = SPACESHIP_GRID_ROWS; row-- > 0; ) {
		for (size_t col = SPACESHIP_GRID_COLS; col-- > 0; ) {
			if (blocks.at(row, col) != SpaceshipBlock::NONE) {
				if (!foundBottom) {
					result.row = row;
					foundBottom = true;
				}
				result.col = std::max(col, result.col);
				break;
			}
		}
	}
	return result;
}

size_t SpaceshipData::getEngineCount() const
{
	return engines.size();
}


