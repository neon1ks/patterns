#include <iostream>

#include "LevelGUI.h"
#include "MyTools.h"

#include <cstring>

using namespace std;
using namespace MyTools;

void LevelGUI::Draw() const
{
    MyTools::SetColor(CC_White);

    GotoXY(x, y);
    char *buf = new (nothrow) char[width + 1];
    if (buf == nullptr) {
        return;
    }
    memset(buf, '+', width);
    buf[width] = '\0';
    cout << buf;
    GotoXY(x, y + height);
    cout << buf;
    delete[] buf;
    buf = nullptr;

    for (auto i = static_cast<size_t>(y); i < static_cast<size_t>(height + y); i++) {
        GotoXY(x, static_cast<double>(i));
        cout << "+";
        GotoXY(x + width - 1, static_cast<double>(i));
        cout << "+";
    }

    GotoXY(3, 1);
    if (passedTime != 0) {
        cout << "FramePerSecond: " << (fps * 1000 / passedTime);
    }
    GotoXY(25, 1);
    cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    GotoXY(46, 1);
    cout << "BombsNum: " << bombsNumber;
    GotoXY(62, 1);
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
