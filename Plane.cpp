
#include <iostream>

#include "Plane.h"
#include "ScreenSingleton.h"

using namespace std;

void Plane::Draw() const
{
    auto &screen = ScreenSingleton::getInstance();
    screen.SetColor(CC_LightBlue);
    screen.GotoXY(x, y);
    cout << "=========>";
    screen.GotoXY(x - 2, y - 1);
    cout << "===";
    screen.GotoXY(x + 3, y - 1);
    cout << R"---(\\\\)---";
    screen.GotoXY(x + 3, y + 1);
    cout << "////";
}
