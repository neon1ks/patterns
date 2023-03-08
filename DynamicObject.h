#pragma once

#include <cstdint>

#include "GameObject.h"

class DynamicObject : public GameObject
{
public:
    DynamicObject() = default;

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

protected:
    double speed = 0.0;
    double xDirction = 0.0;
    double yDirection = 0.0;
};
