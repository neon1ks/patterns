#pragma once

#include <stdint.h>

#include <vector>
#include <string>

#include "DestroyableGroundObject.h"

class House : public DestroyableGroundObject
{
public:
    bool __fastcall isInside(double x1, double x2) const override;

    inline uint16_t GetScore() const override { return score; }

    void Draw() const override;

    void setLine(size_t index, const std::string &line);
    void resetLine(size_t index);

private:
    const uint16_t score = 40;

    std::vector<std::string> lines;
};

class HouseBuilder
{
protected:
    House *house = nullptr;

public:
    virtual void createHouse()
    {
        if (house != nullptr) {
            delete house;
        }
        house = new House();
    }

    House *getHouse()
    {
        House *result = house;
        house = nullptr;
        return result;
    }

    virtual void addRoof();
    virtual void addWindows();
    virtual void addWalls();

    virtual ~HouseBuilder() { delete house; }
};

class NormalHouseBuilder : public HouseBuilder
{
public:
    void addRoof() override;
    void addWindows() override;
    void addWalls() override;
};

class HouseWithTwoWindowsBuilder : public HouseBuilder
{
public:
    void addRoof() override;
    void addWindows() override;
    void addWalls() override;
};

class DesertHouseBuilder : public HouseBuilder
{
public:
    void addRoof() override;
    void addWindows() override;
    void addWalls() override;
};

House *createHouse(HouseBuilder *builder);
