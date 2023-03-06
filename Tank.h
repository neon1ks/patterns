#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

class Tank : public DestroyableGroundObject
{
public:
    Tank() = default;

    bool __fastcall isInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override { return score; }

    void Draw() const override;

    [[nodiscard]] Tank *Clone() const override;

private:
    Tank(const Tank& tank);

    const uint16_t score = 30;
};
