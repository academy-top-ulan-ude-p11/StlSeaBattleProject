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

