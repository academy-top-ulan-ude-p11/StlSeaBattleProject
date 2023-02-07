#pragma once
#include <iostream>
#include <vector>
#include <iomanip>

#include "Ship.h"
#include "Console.h"

using namespace std;

class ISetFlotilla
{
public:
	virtual vector<Ship> SetShips() = 0;
};

class SetFlotillaKeyboard : public ISetFlotilla
{
	Ship InputShip(int size)
	{
		char letter;
		int number;
		char direction;

		Point point;
		Direction dir;

		cout << "input point:\n";
		while (true)
		{
			cout << "\tinput letter: ";
			cin >> letter;
			letter = tolower(letter);
			if (letter >= 97 && letter <= 106)
				break;
		}
		while (true)
		{
			cout << "\tinput number: ";
			cin >> number;
			if (number >= 1 && number <= 10)
				break;
		}
		while (true)
		{
			cout << "input direction <h, v>: ";
			cin >> direction;
			direction = tolower(direction);
			if (direction == 104 || direction == 118)
				break;
		}
		point.row = number - 1;
		point.col = letter - 97;
		dir = (direction == 104) ? Direction::Horizontal : Direction::Vertical;

		return Ship(point, size, dir);
	}
public:
	vector<Ship> SetShips() override
	{
		vector<Ship> flotilla;

		//flotilla.push_back(Ship(2, 6, 4, Direction::Horizontal));
		flotilla.push_back(Ship(0, 4, 3, Direction::Vertical));
		/*flotilla.push_back(Ship(4, 5, 3, Direction::Horizontal));
		flotilla.push_back(Ship(1, 2, 2, Direction::Vertical));
		flotilla.push_back(Ship(4, 2, 2, Direction::Vertical));
		flotilla.push_back(Ship(9, 3, 2, Direction::Horizontal));
		flotilla.push_back(Ship(0, 9, 1, Direction::Horizontal));
		flotilla.push_back(Ship(5, 0, 1, Direction::Horizontal));
		flotilla.push_back(Ship(7, 3, 1, Direction::Horizontal));
		flotilla.push_back(Ship(6, 6, 1, Direction::Horizontal));*/
		/*
		for (int s = 4; s > 0; s--)
		{
			for (int i = s; i < 5; i++)
			{
				cout << "input " << s << "-decks ship : \n";
				flotilla.push_back(InputShip(s));
			}
		}
		*/
		return flotilla;
	}
};

class SetFlotillaConsole : public ISetFlotilla
{
	Console console;
	int sizeField;

	Point beginField;
	Point endField;

	vector<Ship> flotilla;
public:
	SetFlotillaConsole() 
	{
		sizeField = 10;
		beginField.row = 2;
		beginField.col = 4;
		endField.row = beginField.row + sizeField;
		endField.col = beginField.col + sizeField * 2;
	}

	void View(int size, int count)
	{
		console.Clear();

		// view coordinats
		console.SetForeground(Colors::White, true);
		for (int i = 0; i < sizeField; i++)
		{
			console.CursorGoTo(beginField.row - 1, beginField.col + i * 2);
			cout << setw(2) << (char)(i + 'a');
			console.CursorGoTo(beginField.row + i, beginField.col - 2);
			cout << setw(2) << i + 1;
		}
		
		// view water
		console.SetForeground(Colors::Cyan);
		for (int row = 0; row < sizeField; row++)
		{
			for (int col = 0; col < sizeField; col++)
			{
				console.CursorGoTo(beginField.row + row, beginField.col + col * 2);		
				cout << setw(2) << string(2, WATER);
			}
		}

		// view ships on field
		console.SetForeground(Colors::Magenta);
		for (Ship ship : flotilla)
		{
			int row = ship.Row();
			int col = ship.Col();
			for (int s = 0; s < ship.Size(); s++)
			{
				console.CursorGoTo(beginField.row + row, beginField.col + col * 2);
				cout << string(2, DESK);
				if (ship.Direction() == Direction::Horizontal)
					col++;
				else
					row++;
			}
		}


		
		// view ships for setup
		int diffCol = endField.col + 10;
		for (int shipSize = 4, i = 0; shipSize > 0; shipSize--, i++)
		{
			console.SetForeground(Colors::White, true);
			console.CursorGoTo(beginField.row + i * 2, diffCol);
			if (size < shipSize)
				cout << 0;
			else if (size == shipSize)
				cout << 5 - count;
			else
				cout << 5 - shipSize;
			
			if (shipSize == size)
				console.SetForeground(Colors::Green);
			else
				console.SetForeground(Colors::Magenta);

			for (int s = 0; s < shipSize; s++)
			{
				console.CursorGoTo(beginField.row + i * 2, diffCol + s * 2 + 2);
				cout << setw(2) << string(2, DESK);
			}
		}
	}

	void ViewCurrentShip(Ship ship)
	{
		int r = endField.row + 1;
		int c = beginField.col;
		console.SetForeground(Colors::Gray);
		for (int i = 0; i < ship.Size(); i++)
			for (int j = 0; j < ship.Size(); j++)
			{
				console.CursorGoTo(r + i, c + j * 2);
				cout << setw(2) << string(2, DESK);
			}
				

		r = endField.row + 1;
		c = beginField.col;
		console.SetForeground(Colors::Green);
		for (int i = 0; i < ship.Size(); i++)
		{
			console.CursorGoTo(r, c);
			cout << setw(2) << string(2, DESK);
			if (ship.Direction() == Direction::Horizontal)
				c+=2;
			else
				r++;
		}
	}

	Ship SetShip(int shipSize)
	{
		KeyCode key;
		int row{};
		int col{};
		console.CursorGoTo(beginField.row + row, beginField.col + col * 2);

		Ship* ship = new Ship(row, col, shipSize, Direction::Horizontal);

		ViewCurrentShip(*ship);
		
		/*console->SetForeground(Colors::Magenta, true);
		cout << setw(2) << string(2, DESK);
		console->CursorGoTo(beginField.row + row, beginField.col + col * 2);*/

		bool isWrong{ true };
		while (1)
		{
			key = (KeyCode)_getch();
			
			switch (key)
			{
			case ArrowUp:
				if (row > 0)
					row--;
				break;
			case ArrowDown:
				if (row < sizeField - 1)
					row++;
				break;
			case ArrowLeft:
				if (col > 0)
					col--;
				break;
			case ArrowRight:
				if (col < sizeField - 1)
					col++;
				break;
			case Enter:
				isWrong = false;
				if (ship->Direction() == Direction::Horizontal)
					isWrong = col + ship->Size() > 10;
				else
					isWrong = row + ship->Size() > 10;
				if (isWrong)
					break;

				for (Ship s : flotilla)
				{
					int r = row; //ship.GetPoint().row;
					int c = col; //ship.GetPoint().col;
					for (int i = 0; i < ship->Size(); i++)
					{
						for (int rx = -1; rx < 2; rx++)
						{
							for (int cx = -1; cx < 2; cx++)
							{
								isWrong = s.IsPoint(Point(r + rx, c + cx));
								if (isWrong) break;
							}
							if (isWrong) break;
						}
						if (isWrong) break;
						if (ship->Direction() == Direction::Horizontal)
							c++;
						else
							r++;
					}
					if (isWrong)
						break;
				}
				if (!isWrong)
				{
					ship->Row() = row;
					ship->Col() = col;
				}
				break;
			case Space:
				if (ship->Direction() == Direction::Horizontal)
					ship->Direction() = Direction::Vertical;
				else
					ship->Direction() = Direction::Horizontal;
				ViewCurrentShip(*ship);
				break;
			case Esc:
				exit(1);
				break;
			default:
				break;
			}
			
			console.CursorGoTo(beginField.row + row, beginField.col + col * 2);
			if (!isWrong)
				break;
		}
		return *ship;
	}

	vector<Ship> SetShips() override
	{
		
		flotilla.push_back(Ship(2, 6, 4, Direction::Horizontal));
		flotilla.push_back(Ship(0, 4, 3, Direction::Vertical));
		flotilla.push_back(Ship(4, 5, 3, Direction::Horizontal));
		flotilla.push_back(Ship(1, 2, 2, Direction::Vertical));
		flotilla.push_back(Ship(4, 2, 2, Direction::Vertical));
		flotilla.push_back(Ship(9, 3, 2, Direction::Horizontal));
		flotilla.push_back(Ship(0, 9, 1, Direction::Horizontal));
		flotilla.push_back(Ship(5, 0, 1, Direction::Horizontal));
		flotilla.push_back(Ship(7, 3, 1, Direction::Horizontal));
		flotilla.push_back(Ship(6, 6, 1, Direction::Horizontal));
		
		/*
		for (int shipSize = 4; shipSize > 0; shipSize--)
		{
			for (int shipCount = shipSize; shipCount < 5; shipCount++)
			{
				View(shipSize, shipCount);
				Ship ship = SetShip(shipSize);
				flotilla.push_back(ship);
			}
		}
		*/
		return flotilla;
	}
};