
#include <iostream>

#include "Bomb.h"
#include "ScreenSingleton.h"

#include "Visitor.h"

using namespace std;

void Bomb::Draw() const
{
    auto &screen = ScreenSingleton::getInstance();
    screen.SetColor(CC_LightMagenta);
    screen.GotoXY(x, y);
    cout << "*";
}

void Bomb::Accept(const Visitor &v)
{
    v.log(*this);
}
