#include <iostream>
#include "Game.h"
#include "Platform.h"

#include "Console.h"

int main()
{
    Platform* platformKeyboard = new Platform(new GamePlatformConsole(),
                                              new SetShotConsole(),
                                              new SetFlotillaConsole());
    Game game(platformKeyboard);

    game.Setup();
    game.SetFlotilla();
    game.View();

    game.Process();

    

}
