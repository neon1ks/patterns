#include <conio.h>

#include "SBomber.h"
#include "Logger.h"
#include "ScreenSingleton.h"

using namespace std;

//========================================================================================================================

int main()
{

    Logger::getInstance().OpenLogFile("log.txt");

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit()) {
            game.ProcessKBHit();
        }

        ScreenSingleton::getInstance().ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    Logger::getInstance().CloseLogFile();

    return 0;
}
