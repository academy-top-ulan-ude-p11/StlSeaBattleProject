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
	Ship(Point point, int size, Direction direction)
		: point{ point },
		size{ size },
		direction{ direction },
		damage{ 0 } {}
	
	int Size() { return size; }
	Direction Direction() { return direction; }
	int& Damage() { return damage; }

	bool IsDead() { size == damage; }
};

