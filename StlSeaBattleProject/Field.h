#pragma once
#include <vector>
#include "Cell.h"

using namespace std;

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
};

