// SpaceInvatertConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "gameGrid.h"
#include "player.h"
#include "gameLoop.h"
#include <stdio.h>
#include <string>
#include "setting.h"




int main()
{

    Game newGame;
    //newGame.testGameLoop();
    newGame.mainGameLoop(4);
    //std::thread thread(timer, 1000, updaterender();
    //thread.join();
    system("pause");
}
