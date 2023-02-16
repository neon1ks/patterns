
#include <iostream>

#include "Tank.h"
#include "ScreenSingleton.h"

using namespace std;

bool Tank::isInside(double x1, double x2) const
{
    const double XBeg = x + 2;
    const double XEnd = x + width - 1;

    if (x1 < XBeg && x2 > XEnd) {
        return true;
    }

    if (x1 > XBeg && x1 < XEnd) {
        return true;
    }

    if (x2 > XBeg && x2 < XEnd) {
        return true;
    }

    return false;
}

void Tank::Draw() const
{
    auto &screen = ScreenSingleton::getInstance();

    screen.SetColor(CC_Brown);
    screen.GotoXY(x, y - 3);
    cout << "    #####";
    screen.GotoXY(x - 2, y - 2);
    cout << "#######   #";
    screen.GotoXY(x, y - 1);
    cout << "    #####";
    screen.GotoXY(x, y);
    cout << " ###########";
}
