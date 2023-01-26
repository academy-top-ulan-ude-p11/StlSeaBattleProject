#pragma once
#include "IGamePlatform.h"
#include "ISetShot.h"
#include "ISetFlotilla.h"

class Platform
{
	IGamePlatform* gamePlatform;
	ISetShot* shooter;
	ISetFlotilla* commander;
public:
	Platform(IGamePlatform* gamePlatform,
		ISetShot* shooter,
		ISetFlotilla* commander)
		: gamePlatform{ gamePlatform },
		shooter{ shooter }, 
		commander{ commander } {}
	IGamePlatform* GamePlatform(){ return gamePlatform; }
	ISetShot* Shooter() { return shooter; }
	ISetFlotilla* Commander() { return commander; }
};

