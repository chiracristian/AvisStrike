#pragma once

#include <vector>

enum class Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

constexpr Direction DIRECTIONS[4] = {
	Direction::UP,
	Direction::DOWN,
	Direction::LEFT,
	Direction::RIGHT
};

struct Array2DPos
{
	size_t row;
	size_t col;

	Array2DPos() : row(0), col(0) {};
	Array2DPos(size_t row, size_t col) : row(row), col(col) {}

	bool operator==(const Array2DPos& other) const
	{
		return row == other.row && col == other.col;
	}

	Array2DPos step(Direction direction) const
	{
		switch (direction) {
		case Direction::UP:
			return Array2DPos(row - 1, col);

		case Direction::DOWN:
			return Array2DPos(row + 1, col);

		case Direction::LEFT:
			return Array2DPos(row, col - 1);

		case Direction::RIGHT:
			return Array2DPos(row, col + 1);
		}

		return Array2DPos(row, col);
	}

	bool canStep(Direction direction, size_t rows, size_t cols) const
	{
		switch (direction) {
		case Direction::UP:
			if (row == 0) {
				return false;
			}
			break;

		case Direction::DOWN:
			if (row == rows - 1) {
				return false;
			}
			break;

		case Direction::LEFT:
			if (col == 0) {
				return false;
			}
			break;

		case Direction::RIGHT:
			if (col == cols - 1) {
				return false;
			}
			break;
		}
		return true;
	}
};

template <typename T>
class Array2D
{
public:
	Array2D(size_t rows, size_t cols)
		: rows(rows), cols(cols),
		data(rows * cols)
	{

	}

	Array2D(size_t rows, size_t cols, T defaultValue)
		: rows(rows), cols(cols),
		data(rows * cols, defaultValue)
	{
		
	}

	T& at(size_t row, size_t col)
	{
		return data[row * cols + col];
	}

	const T& at(size_t row, size_t col) const
	{
		return data[row * cols + col];
	}

	T& at(Array2DPos pos)
	{
		return data[pos.row * cols + pos.col];
	}

	const T& at(Array2DPos pos) const
	{
		return data[pos.row * cols + pos.col];
	}

	void fill(T value)
	{
		for (size_t i = 0; i < data.size(); i++) {
			data[i] = value;
		}
	}

	size_t getRows() const
	{
		return rows;
	}

	size_t getCols() const
	{
		return cols;
	}

private:
	size_t rows;
	size_t cols;

	std::vector<T> data;
};
