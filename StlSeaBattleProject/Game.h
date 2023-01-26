#pragma once
#include <vector>

#include "Player.h"
#include "IGamePlatform.h"
#include "Platform.h"

class Game
{
	vector<Player> players;
	bool currentPlayer{ false };

	Platform* platform;
public:
	Game() : Game(nullptr) {}
	Game(Platform* platform)
		: platform{ platform }
	{
		players.resize(2, Player());
		for (int i = 0; i < players.size(); i++)
		{
			players[i].Shooter() = platform->Shooter();
			players[i].Commander() = platform->Commander();
		}
	}

	//vector<Player> Players() { return players; }

	void Setup()
	{
		platform->GamePlatform()->Setup(players);
		
	}

	void View()
	{
		platform->GamePlatform()->ViewGame(players);
	}
	void SetFlotilla()
	{
		for (int i = 0; i < players.size(); i++)
		{
			cout << "Player #" << i + 1 << "set of sips:\n";
			players[i].SetFlotilla();
		}
			
	}

	void Process()
	{
		currentPlayer = false;
		while (true)
		{
			Point pointShot = players[currentPlayer].SetShot();
			players[!currentPlayer].GetShot(pointShot);
			vector<Ship> flotilla = players[!currentPlayer].GetFlotilla();
		
			bool isDefeat = false;
		}
	}

};

