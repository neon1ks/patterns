#pragma once

#include <cstdint>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:
    [[nodiscard]] bool __fastcall isInside(double x1, double x2) const override;

    [[nodiscard]] inline uint16_t GetScore() const override { return score; }

    void Draw() const override;

private:
    const uint16_t score = 40;
};
