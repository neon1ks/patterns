#include <iostream>

#include "LevelGUI.h"
#include "ScreenSingleton.h"

#include <cstring>

using namespace std;

void LevelGUI::Draw() const
{
    auto &screen = ScreenSingleton::getInstance();

    screen.SetColor(CC_White);

    screen.GotoXY(x, y);
    char *buf = new (nothrow) char[width + 1];
    if (buf == nullptr) {
        return;
    }
    memset(buf, '+', width);
    buf[width] = '\0';
    cout << buf;
    screen.GotoXY(x, y + height);
    cout << buf;
    delete[] buf;
    buf = nullptr;

    for (auto i = static_cast<size_t>(y); i < static_cast<size_t>(height + y); i++) {
        screen.GotoXY(x, static_cast<double>(i));
        cout << "+";
        screen.GotoXY(x + width - 1, static_cast<double>(i));
        cout << "+";
    }

    screen.GotoXY(3, 1);
    if (passedTime != 0) {
        cout << "FramePerSecond: " << (fps * 1000 / passedTime);
    }
    screen.GotoXY(25, 1);
    cout << "PassedTime: " << (passedTime / 1000) << " sec";
    screen.GotoXY(46, 1);
    cout << "BombsNum: " << bombsNumber;
    screen.GotoXY(62, 1);
    cout << "Score: " << score;
}

void __fastcall LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew,
                                   int scoreNew)
{
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}
