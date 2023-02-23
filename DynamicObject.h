#pragma once

#include <cstdint>
#include <utility>

#include "GameObject.h"

class Visitor;

class DynamicObject : public GameObject
{
public:
    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    ~DynamicObject() = default;

    inline void SetSpeed(double sp) { speed = sp; }
    inline void SetDirection(double dx, double dy)
    {
        xDirction = dx;
        yDirection = dy;
    }

    virtual void Move(uint16_t time)
    {
        x += xDirction * speed * time * 0.001;
        y += yDirection * speed * time * 0.001;
    };

    double GetSpeed() const { return speed; }
    std::pair<double, double> GetDirection() const { return { xDirction, yDirection }; }

    virtual void Accept(const Visitor &v) = 0;

protected:
    double speed;
    double xDirction, yDirection;
};
