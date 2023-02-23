#include "Visitor.h"

#include "Logger.h"

#include <sstream>

using namespace std;

void LogVisitor::log(const Bomb &b) const
{
    auto speed = b.GetSpeed();
    auto [dx, dy] = b.GetDirection();

    std::ostringstream ss;
    ss << "Bomb speed = " << speed << ", dx = " << dx << ", dy = " << dy;

    Logger::getInstance().WriteToLog(ss.str());
}

void LogVisitor::log(const Plane &p) const
{
    auto speed = p.GetSpeed();
    auto [dx, dy] = p.GetDirection();

    std::ostringstream ss;
    ss << "Plane speed = " << speed << ", dx = " << dx << ", dy = " << dy;

    Logger::getInstance().WriteToLog(ss.str());
}
