#include <iostream>
#include "Game.h"
#include "Platform.h"

int main()
{
    Platform* platformKeyboard = new Platform(new GamePlatformKeyboard(),
                                              new SetShotKeyboard(),
                                              new SetFlotillaKeyboard());
    Game game(platformKeyboard);

    // выбор вариантов игроков
    //game.Setup();
    game.SetFlotilla();
    game.View();

    game.Process();


}
