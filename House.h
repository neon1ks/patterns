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

private:
    const uint16_t score = 40;

    std::vector<std::string> lines;
};

class HouseBuilder
{
protected:
    House *house = nullptr;

public:
    virtual void createHouse() { house = new House(); }

    House *getHouse()
    {
        House *result = house;
        house = nullptr;
        return result;
    }

    void createRoof(){};
    void createWindow(){};
    void createWalls(){
        house->setLine(0, "############");
    };

    virtual ~HouseBuilder() { delete house; }
};

class NormalHouseBuilder : public HouseBuilder
{
public:
    void createRoof();
    void createWindow();
    void createWalls();
};

House *createHouse(HouseBuilder &builder);
