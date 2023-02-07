#pragma once
#include <vector>

#include "Player.h"
#include "IGamePlatform.h"
#include "Platform.h"

class Game
{
	vector<Player*> players;
	bool currentPlayer{ false };

	Platform* platform;
public:
	Game() : Game(nullptr) {}
	Game(Platform* platform)
		: platform{ platform }
	{
		HumanPlayer* humanPlayer = new HumanPlayer();
		humanPlayer->Shooter() = platform->Shooter();
		humanPlayer->Commander() = platform->Commander();
		players.push_back(humanPlayer);
		players.push_back(new ComputerPlayer());
	}

	//vector<Player> Players() { return players; }

	void Setup()
	{
		platform->GamePlatform()->Setup(players[0]);
	}

	void View()
	{
		platform->GamePlatform()->ViewGame(players);
	}
	void SetFlotilla()
	{
		for (int i = 0; i < players.size(); i++)
		{
			players[i]->SetFlotilla();
		}
	}

	void Process()
	{
		currentPlayer = false;
		HitType hit;

		while (true)
		{
			View();
			Point pointShot = players[currentPlayer]->SetShot();
			hit = players[!currentPlayer]->GetShot(pointShot);

			// Destroy
			if (hit == HitType::Destroy)
				if (players[!currentPlayer]->FlotillaSize() == 0)
					break;

			// Wound

			// Beside
			if (hit == HitType::Beside)
				currentPlayer = !currentPlayer;

			//_getch();
		}

	}

};

