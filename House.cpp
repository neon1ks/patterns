
#include <iostream>

#include "House.h"
#include "ScreenSingleton.h"

using namespace std;

bool House::isInside(double x1, double x2) const
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

void House::Draw() const
{
    auto &screen = ScreenSingleton::getInstance();

    screen.SetColor(CC_Yellow);
    screen.GotoXY(x, y - 5);
    cout << "  ########  ";
    screen.GotoXY(x, y - 4);
    cout << "##        ##";
    screen.GotoXY(x, y - 3);
    cout << "############";
    screen.GotoXY(x, y - 2);
    cout << "#          #";
    screen.GotoXY(x, y - 1);
    cout << "#          #";
    screen.GotoXY(x, y);
    cout << "############";
}

House *House::Clone() const
{
    return new House(*this);
}

House::House(const House &house)
{
    x = house.x;
    y = house.y;
    width = house.width;
}

//House::House
