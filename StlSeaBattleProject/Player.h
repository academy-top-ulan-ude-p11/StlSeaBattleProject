#pragma once
#include <string>

#include "Ship.h"
#include "Field.h"
#include "ISetShot.h"
#include "ISetFlotilla.h"

using namespace std;

class Player
{
	string name;
	Field battlefield;
	vector<Ship> flotilla;

	ISetShot* shooter = nullptr;
	ISetFlotilla* commander = nullptr;
public:
	Player() : Player("") {}
	Player(string name) : name{ name } {}

	string& Name() { return name; }

	ISetShot*& Shooter() { return shooter; }
	ISetFlotilla*& Commander() { return commander; }

	void SetFlotilla() 
	{ 
		flotilla = commander->SetShips();
		// пометить €чейки на игровом поле типом ѕалуба, где это необходимо.
		battlefield.SetShip(flotilla);
	}

	HitType GetShot(Point point) 
	{	
		HitType hit;
		hit = battlefield.CheckShot(point);
		battlefield.SetCellShot(point);

		if (hit == HitType::Beside)
			return hit;

		for (Ship ship : flotilla)
		{
			if (ship.IsPoint(point))
			{
				ship.Damage()++;
				if (ship.IsDead())
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

	Point SetShot() { return shooter->SetShot(); }

	vector<Ship> GetFlotilla() { return flotilla; }
};

