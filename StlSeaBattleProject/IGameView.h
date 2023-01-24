#pragma once
#include "Console.h"

class IGameView
{
public:
	virtual void GameView() = 0;
};

class ConsoleGameView : public IGameView
{
	Console console;
public:
	void GameView() override
	{
		console.Clear();
		
		console.CursorGoTo(0, 0);
		
	}
};
