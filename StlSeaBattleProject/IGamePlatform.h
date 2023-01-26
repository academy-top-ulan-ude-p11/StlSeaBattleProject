#pragma once
#include <conio.h>
#include <iomanip>

#include "Game.h"
#include "Console.h"

class IGamePlatform
{
public:
	virtual void Setup(vector<Player>& players) = 0;
	virtual void ViewGame(vector<Player>& players) = 0;
};


class GamePlatformKeyboard : public IGamePlatform
{
	Console console;
public:
	void Setup(vector<Player>& players) override
	{
		cout << "Welcomw to game \"Sea Battle\"\n";
		for (int i = 0; i < players.size(); i++)
		{
			cout << "input name " << i + 1 << " player: ";
			char name[50];
			cin.getline(name, 50);
			players[i].Name() = string(name);
		}
	}

	void ViewGame(vector<Player>& players) override
	{
		//for (int i = 0; i < players.size(); i++)
		//	cout << players[i].Name() << "\t\t";
		console.Clear();
		int diffCol{ 40 };

		for (int i = 0; i < 10; i++)
		{
			console.CursorGoTo(0, 2 + i * 2);
			cout << setw(2) << i;
			console.CursorGoTo(1 + i, 0);
			cout << i;

			console.CursorGoTo(0, diffCol + 2 + i * 2);
			cout << setw(2) << i;
			console.CursorGoTo(1 + i, diffCol + 0);
			cout << i;
		}
		for(int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{
				console.CursorGoTo(1 + i, 2 + j * 2);
				cout << string(2, WATER);

				console.CursorGoTo(1 + i, diffCol + 2 + j * 2);
				cout << string(2, WATER);
			}
		
		Player player = players[0];
		for (Ship ship : player.GetFlotilla())
		{
			
			int row = ship.Row();
			int col = ship.Col();
			for (int s = 0; s < ship.Size(); s++)
			{
				console.CursorGoTo(1 + row, 2 + col*2);
				cout << string(2, DESK);
				if (ship.Direction() == Direction::Horizontal)
					col++;
				else
					row++;
			}
		}
		char ch = _getch();
		cout << "\n";
	}
};







//class GameControllerConsole : public IGameController
//{
//public:
//	void Setup() override
//	{
//		cout << "Other Game setup\n";
//	}
//};
//

