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
        lines.at(index).resize(line.size(), ' ');
    }

    for (size_t i = 0; i < line.size(); ++i) {
        if (line.at(i) != ' ') {
            lines.at(index).at(i) = line.at(i);
        }
    }
}

void House::resetLine(size_t index)
{
    lines.at(index).clear();
}

void HouseBuilder::addRoof()
{
    house->setLine(6, "  ########  ");
    house->setLine(5, "##        ##");
}

void HouseBuilder::addWindows() { } // Без окон

void HouseBuilder::addWalls()
{
    house->setLine(4, "############");
    house->setLine(3, "#          #");
    house->setLine(2, "#          #");
    house->setLine(1, "#          #");
    house->setLine(0, "############");
}

void NormalHouseBuilder::addRoof()
{
    HouseBuilder::addRoof();
}

void NormalHouseBuilder::addWindows()
{
    house->setLine(3, "     __     ");
    house->setLine(2, "    |__|    ");
}

void NormalHouseBuilder::addWalls()
{
    HouseBuilder::addWalls();
}

void HouseWithTwoWindowsBuilder::addRoof()
{
    HouseBuilder::addRoof();
}

void HouseWithTwoWindowsBuilder::addWindows()
{
    house->setLine(3, "   _    _   ");
    house->setLine(2, "  |_|  |_|  ");
}

void HouseWithTwoWindowsBuilder::addWalls()
{
    HouseBuilder::addWalls();
}

void DesertHouseBuilder::addRoof() { } // Без крыши

void DesertHouseBuilder::addWindows()
{
    house->setLine(3, "   _   __   ");
    house->setLine(2, "  |_| |  |  ");
    house->setLine(1, "      |  |  ");
}

void DesertHouseBuilder::addWalls()
{
    HouseBuilder::addWalls();
}

House *createHouse(HouseBuilder *builder)
{
    builder->createHouse();

    builder->addRoof();
    builder->addWindows();
    builder->addWalls();

    return builder->getHouse();
}
