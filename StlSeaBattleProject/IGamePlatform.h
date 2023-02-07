#pragma once
#include <conio.h>
#include <iomanip>

#include "Game.h"
#include "Console.h"

class IGamePlatform
{
public:
	virtual void Setup(Player* playerHuman) = 0;
	virtual void ViewGame(vector<Player*>& players) = 0;
};

/*
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

*/

class GamePlatformConsole : public IGamePlatform
{
	Console console;

	int sizeField;

	Point beginField;
	Point endField;
public:
	GamePlatformConsole()
	{
		sizeField = 10;
		beginField.row = 2;
		beginField.col = 4;
		endField.row = beginField.row + sizeField;
		endField.col = beginField.col + sizeField * 2;
	}
	void Setup(Player* playerHuman) override
	{
		cout << "Welcomw to game \"Sea Battle\"\n";
		cout << "input name: ";
		char name[50];
		cin.getline(name, 50);
		playerHuman->Name() = string(name);
	}

	void ViewGame(vector<Player*>& players) override
	{
		int diffCol{ 40 };
		console.Clear();

		Player* playerHuman = players[0];
		Player* playerComp = players[1];

		// view coordinats
		console.SetForeground(Colors::White, true);
		for (int i = 0; i < sizeField; i++)
		{
			console.CursorGoTo(beginField.row - 1, beginField.col + i * 2);
			cout << setw(2) << (char)(i + 'a');
			console.CursorGoTo(beginField.row + i, beginField.col - 2);
			cout << setw(2) << i + 1;

			console.CursorGoTo(beginField.row - 1, diffCol + beginField.col + i * 2);
			cout << setw(2) << (char)(i + 'a');
			console.CursorGoTo(beginField.row + i, diffCol + beginField.col - 2);
			cout << setw(2) << i + 1;
		}

		
		for (int row = 0; row < sizeField; row++)
			for (int col = 0; col < sizeField; col++)
			{
				if(playerHuman->Battlefield().GetCell(row, col).IsShot())
					console.SetForeground(Colors::Red);
				else
					console.SetForeground(Colors::Cyan);
				console.CursorGoTo(beginField.row + row, beginField.col + col * 2);
				cout << string(2, WATER);


				if (playerComp->Battlefield().GetCell(row, col).IsShot())
				{
					console.SetForeground(Colors::Red);
					console.CursorGoTo(beginField.row + row, diffCol + beginField.col + col * 2);
					if (playerComp->Battlefield().GetCell(row, col).Type() == CellType::Water)
						cout << string(2, WATER);
					else
						cout << string(2, DESK);
				}
				else
				{
					console.CursorGoTo(beginField.row + row, diffCol + beginField.col + col * 2);
					console.SetForeground(Colors::Cyan);
					cout << string(2, WATER);
				}
					
				

				
			}
		
		for (Ship ship : playerHuman->GetFlotilla())
		{
			int row = ship.Row();
			int col = ship.Col();
			for (int s = 0; s < ship.Size(); s++)
			{
				console.CursorGoTo(beginField.row + row, beginField.col + col * 2);
				if (playerHuman->Battlefield().GetCell(row, col).IsShot())
					console.SetForeground(Colors::Red);
				else
					console.SetForeground(Colors::Magenta);
				cout << string(2, DESK);
				if (ship.Direction() == Direction::Horizontal)
					col++;
				else
					row++;
			}
		}

		//char ch = _getch();
		//cout << "\n";
	}
};


