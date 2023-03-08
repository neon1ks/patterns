#include <iostream>

#include "Bomb.h"
#include "ScreenSingleton.h"

using namespace std;

void Bomb::Draw() const
{
    auto &screen = ScreenSingleton::getInstance();
    screen.SetColor(CC_LightMagenta);
    screen.GotoXY(x, y);
    cout << "*";
}
