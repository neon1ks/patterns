#pragma once

#include <cstdint>

class GameObject
{
public:
    GameObject() = default;

    virtual ~GameObject() = default;

    virtual void Draw() const = 0;

    inline void SetPos(double nx, double ny)
    {
        x = nx;
        y = ny;
    }

    [[nodiscard]] inline double GetY() const { return y; }
    [[nodiscard]] inline double GetX() const { return x; }

    inline void SetWidth(uint16_t widthN) { width = widthN; }
    [[nodiscard]] inline uint16_t GetWidth() const { return width; }

protected:
    double x = 0.0;
    double y = 0.0;
    uint16_t width = 0;
};
