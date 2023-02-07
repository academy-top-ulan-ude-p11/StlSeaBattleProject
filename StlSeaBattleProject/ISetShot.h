#pragma once
#include <iostream>
#include <ctype.h>

#include "Cell.h"
#include "Console.h"

using namespace std;

class ISetShot
{
public:
	virtual Point SetShot() = 0;
};

class SetShotKeyboard : public ISetShot
{
public:
	Point SetShot() override
	{
		Console console;

		char letter;
		int number;
		console.CursorGoTo(15, 0);
		cout << "input point of shot (a-j, 1-10)\n";
		while (true)
		{
			cout << "input letter: ";
			cin >> letter;
			letter = tolower(letter);
			if (letter >= 97 && letter <= 106)
				break;
		}
		while (true)
		{
			cout << "input number: ";
			cin >> number;
			if (number >= 1 && number <= 10)
				break;
		}
		return Point(number - 1, letter - 97);
	}
};

class SetShotConsole : public ISetShot
{
	Console console;
	int sizeField;

	Point beginField;
	Point endField;
public:
	SetShotConsole()
	{
		sizeField = 10;
		beginField.row = 2;
		beginField.col = 4;
		endField.row = beginField.row + sizeField;
		endField.col = beginField.col + sizeField * 2;
	}

	Point SetShot() override
	{
		KeyCode key;
		int row{};
		int col{};
		int diffCol{ 40 };
		console.CursorGoTo(beginField.row + row, diffCol + beginField.col + col * 2);

		bool isShot{ false };
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
				isShot = true;
				break;
			case Esc:
				exit(1);
				break;
			default:
				break;
			}

			console.CursorGoTo(beginField.row + row, diffCol + beginField.col + col * 2);
			if (isShot)
				break;
		}
		return Point(row, col);
	}
};
