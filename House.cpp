#include <algorithm>
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

    for (size_t i = lines.size(); i > 0; --i) {
        screen.GotoXY(x, y - i + 1);
        cout << lines.at(i - 1);
    }
}

void House::setLine(size_t index, const std::string &line)
{
    if (index >= lines.size()) {
        lines.resize(index + 1);
    }

    if (lines.at(index).size() < line.size()) {
        lines.at(index).resize(line.size());
    }

    for (size_t i = 0; i < line.size(); ++i) {
        if (line.at(0) != ' ') {
            lines.at(index).at(i) = line.at(0);
        }
    }
}

void NormalHouseBuilder::createRoof()
{
    house->setLine(6, "  ########  ");
    house->setLine(5, "##        ##");
}

void NormalHouseBuilder::createWindow()
{
    house->setLine(3, "     __     ");
    house->setLine(2, "    |  |    ");
    house->setLine(1, "     --     ");
}

void NormalHouseBuilder::createWalls()
{
    house->setLine(4, "############");
    house->setLine(3, "#          #");
    house->setLine(2, "#          #");
    house->setLine(1, "#          #");
    house->setLine(0, "############");
}

House *createHouse(HouseBuilder &builder)
{
    builder.createHouse();
    builder.createRoof();
    builder.createWindow();
    builder.createWalls();
    return builder.getHouse();
}
