#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

#include "ICharacter.h"

class Tank : public DestroyableGroundObject, public ICharacter
{
public:
    Tank(Mediator *m, const std::string &n) : ICharacter(m), name(n) { }

    bool __fastcall isInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override { return score; }

    void Draw() const override;

    void beNotified(const std::string &message, ICharacter const *const character) override {
    } // Empty
    void sendMessage(const std::string &message) override;

    std::string getName() const override { return name; }

private:
    std::string name;
    const uint16_t score = 30;
};
