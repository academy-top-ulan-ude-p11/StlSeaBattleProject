#pragma once
#include <string>

#include "Ship.h"
#include "Field.h"
#include "ISetShot.h"
#include "ISetFlotilla.h"

using namespace std;

class Player
{
protected:
	string name;
	Field battlefield;
	vector<Ship> flotilla;
public:
	Player(string name) : name{ name } {}

	string& Name() { return name; }

	Field& Battlefield() { return battlefield; }

	HitType GetShot(Point point)
	{
		HitType hit;
		hit = battlefield.CheckShot(point);
		battlefield.SetCellShot(point);

		if (hit == HitType::Beside)
			return hit;

		for (int i = 0; i < flotilla.size(); i++)
		{
			if (flotilla[i].IsPoint(point))
			{
				flotilla[i].Damage()++;
				if (flotilla[i].IsDead())
					return HitType::Destroy;
				else
					return HitType::Wound;
			}
		}
	}

	int FlotillaSize()
	{
		int count{};
		for (Ship ship : flotilla)
			if (!ship.IsDead())
				count++;
		return count;
	}

	vector<Ship> GetFlotilla() { return flotilla; }

	virtual Point SetShot() = 0;

	virtual void SetFlotilla() = 0;
};

class HumanPlayer : public Player
{
	ISetShot* shooter = nullptr;
	ISetFlotilla* commander = nullptr;
public:
	HumanPlayer() : HumanPlayer("") {}
	HumanPlayer(string name) : Player(name) {}

	ISetShot*& Shooter() { return shooter; }
	ISetFlotilla*& Commander() { return commander; }

	void SetFlotilla() override
	{ 
		flotilla = commander->SetShips();
		// пометить €чейки на игровом поле типом ѕалуба, где это необходимо.
		battlefield.SetShip(flotilla);
	}

	Point SetShot() override
	{ 
		return shooter->SetShot(); 
	}
};

class ComputerPlayer : public Player
{
public:
	ComputerPlayer() : Player("Computer") {}

	void SetFlotilla() override
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

		battlefield.SetShip(flotilla);
	}

	Point SetShot() override
	{
		srand(time(nullptr));

		return Point((rand() % 10), (rand() % 10));
	}
};
