#include <iostream>

#include "MyTools.h"
#include "Ground.h"

#include <cstring>

using namespace std;
using namespace MyTools;

//==================================================================================================

void Crater::Draw() const
{
    if (width == SMALL_CRATER_SIZE) // Рисование воронки в 9 символов шириной
    {
        GotoXY(x - 4, y + 1);
        cout << "==     ==";
        GotoXY(x - 2, y + 2);
        cout << "=====";
    }
}

bool Crater::isInside(double xn) const
{
    const auto size_2 = width / 2.0;
    const auto value = static_cast<int>(xn);
    return value > static_cast<int>(x - size_2) && value <= static_cast<int>(x + size_2);
}

//==================================================================================================

void Ground::Draw() const
{
    MyTools::SetColor(CC_Green);

    const size_t bufSize = width + 1;
    char *buf = new (nothrow) char[bufSize];
    if (buf == nullptr) {
        return;
    }

    if (vecCrates.empty()) {
        GotoXY(x, y);

        memset(buf, '=', bufSize);
        buf[bufSize - 1] = '\0';
        cout << buf;
    } else {
        const auto X = static_cast<size_t>(x);
        char c = {};
        for (size_t i = X; i < width + X; i++) {
            c = (isInsideAnyCrater(static_cast<double>(i))) ? ' ' : '=';
            buf[i - X] = c;
        }

        GotoXY(static_cast<double>(X), y);
        buf[bufSize - 1] = '\0';
        cout << buf;

        for (const auto &vecCrate : vecCrates) {
            vecCrate.Draw();
        }
    }

    delete[] buf;
}

bool Ground::isInsideAnyCrater(double x) const
{
    bool isInside = false;
    for (const auto &vecCrate : vecCrates) {
        if (vecCrate.isInside(x)) {
            isInside = true;
            break;
        }
    }

    return isInside;
}

void Ground::AddCrater(double xn)
{
    Crater cr;
    cr.SetPos(xn, y);
    cr.SetWidth(SMALL_CRATER_SIZE);
    vecCrates.push_back(cr);
}
