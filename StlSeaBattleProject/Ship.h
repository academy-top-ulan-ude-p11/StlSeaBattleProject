#pragma once
#include "Cell.h"

enum Direction
{
	Horizontal,
	Vertical
};

class Ship
{
	Point point;
	int size;
	Direction direction;
	int damage;
public:
	Ship(int row, int col, int size, Direction direction)
		: Ship(Point(row, col), size, direction) {}

	Ship(Point point, int size, Direction direction)
		: point{ point },
		size{ size },
		direction{ direction },
		damage{ 0 } {}
	
	Point GetPoint(){ return point; }
	
	int Row() { return point.row; }
	int Col() { return point.col; }

	int Size() { return size; }
	Direction Direction() { return direction; }
	int& Damage() { return damage; }

	bool IsDead() { return size == damage; }

	bool IsPoint(Point point)
	{
		bool isPoint = true;
		int row = this->point.row;
		int col = this->point.col;
		for (int i = 0; i < size; i++)
		{
			if (!(point.row == row && point.col == col))
			{
				isPoint = false;
				break;
			}
		}
		return isPoint;
	}
};

