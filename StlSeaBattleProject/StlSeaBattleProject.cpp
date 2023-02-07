#include <iostream>
#include "Game.h"
#include "Platform.h"

#include "Console.h"

int main()
{
    Platform* platformConsole = new Platform(new GamePlatformConsole(),
                                              new SetShotConsole(),
                                              new SetFlotillaConsole());
    Game game(platformConsole);

    game.Setup();
    game.SetFlotilla();
    game.View();

    game.Process();

    

}
