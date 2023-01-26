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
	}

	void GetShot(Point point) {	battlefield.SetCellShot(point);	}

	Point SetShot() { return shooter->SetShot(); }

	vector<Ship> GetFlotilla() { return flotilla; }
};

