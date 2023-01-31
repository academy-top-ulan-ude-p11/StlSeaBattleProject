#include <iostream>
#include "Game.h"
#include "Platform.h"

#include "Console.h"

int main()
{
    Console* console = new Console();

    Platform* platformKeyboard = new Platform(new GamePlatformKeyboard(),
                                              new SetShotKeyboard(),
                                              new SetFlotillaConsole(console));
    Game game(platformKeyboard);

    // выбор вариантов игроков
    game.Setup();
    game.SetFlotilla();
    //game.View();

    //game.Process();

    
}
