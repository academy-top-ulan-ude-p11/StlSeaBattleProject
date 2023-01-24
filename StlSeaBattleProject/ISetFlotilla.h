#pragma once
#include <iostream>
#include <vector>
#include "Ship.h"

using namespace std;

class ISetFlotilla
{
public:
	virtual vector<Ship> SetShips() = 0;
};

class KeyboardSetFlotilla : public ISetFlotilla
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

		for (int s = 4; s > 0; s--)
		{
			for (int i = s; i < 5; i++)
			{
				cout << "input " << s << "-decks ship : \n";
				flotilla.push_back(InputShip(s));
			}
		}

	}
};