#pragma once

#include <cstdint>

#include "GameObject.h"

class DestroyableGroundObject : public GameObject
{
public:
    [[nodiscard]] virtual bool __fastcall isInside(double x1, double x2) const = 0;

    [[nodiscard]] virtual inline uint16_t GetScore() const = 0;

protected:
};
