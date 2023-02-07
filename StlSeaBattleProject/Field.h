#pragma once
#include <vector>
#include "Cell.h"
#include "Ship.h"

using namespace std;

enum HitType
{
	Beside,
	Reach,
	Wound,
	Destroy
};

class Field
{
	const int size{ 10 };
	vector<vector<Cell>> cells;
public:
	Field()
	{
		for (int i = 0; i < size; i++)
		{
			vector<Cell> line;
			for (int j = 0; j < size; j++)
				line.push_back(Cell(Point(i, j)));
			cells.push_back(line);
		}		
	}
	void SetCellType(Point point, CellType type)
	{
		cells[point.row][point.col].Type() = type;
	}
	void SetCellShot(Point point)
	{
		cells[point.row][point.col].IsShot() = true;
	}
	void SetShip(vector<Ship> flotilla)
	{
		for (Ship ship : flotilla)
		{
			int row = ship.Row();
			int col = ship.Col();
			for (int i = 0; i < ship.Size(); i++)
			{
				SetCellType(Point(row, col), CellType::Deck);
				(ship.Direction() == Direction::Horizontal) ? col++ : row++;
			}
		}
	}

	HitType CheckShot(Point point)
	{
		if (cells[point.row][point.col].IsShot() == true)
			return HitType::Beside;

		if(cells[point.row][point.col].Type() == CellType::Water)
			return HitType::Beside;

		if (cells[point.row][point.col].Type() == CellType::Deck)
			return HitType::Reach;
	}

	Cell GetCell(int row, int col)
	{
		return cells[row][col];
	}
};

