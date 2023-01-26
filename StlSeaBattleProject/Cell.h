#pragma once
struct Point
{
	int row;
	int col;
	Point(int row, int col) : row{ row }, col{ col } {}
	Point() : Point(0, 0){}
	
};

enum CellType
{
	Empty,
	Water,
	Deck
};

class Cell
{
	Point point;
	CellType type;
	bool isShot;
public:
	Cell(Point point)
		: point{ point },
		type{ CellType::Empty },
		isShot{ false } {}
	Cell()
		: Cell(Point(0, 0)) {}
	
	Cell(int row, int col)
		: Cell(Point(row, col)) {}
	
	CellType& Type() { return type; }
	bool& IsShot() { return isShot; }
};

