#pragma once

#include <vector>

#include "Bomb.h"
#include "DynamicObject.h"

class BombIterator
{
    std::vector<DynamicObject *> &refArr;
    size_t curIndex;

public:
    BombIterator(std::vector<DynamicObject *> &ref, size_t index = 0) : refArr(ref), curIndex(index)
    {
        if (curIndex > refArr.size()) {
            curIndex = refArr.size();
        }
    }

    friend class BombConstIterator;

    BombIterator &operator++();
    BombIterator &operator--();
    Bomb *operator*();
};

class BombConstIterator
{
    const std::vector<DynamicObject *> &refArr;
    size_t curIndex;

    void check()
    {
        if (curIndex > refArr.size()) {
            curIndex = refArr.size();
        }
    }

public:
    BombConstIterator(const std::vector<DynamicObject *> &ref, size_t index = 0)
        : refArr(ref), curIndex(index)
    {
        check();
    }
    BombConstIterator(const BombIterator &it) : refArr(it.refArr), curIndex(it.curIndex)
    {
        check();
    }

    BombConstIterator &operator++();
    BombConstIterator &operator--();
    Bomb *operator*();

    friend bool operator==(const BombConstIterator &l, const BombConstIterator &r);
};

bool operator==(const BombConstIterator &l, const BombConstIterator &r);
bool operator!=(const BombConstIterator &l, const BombConstIterator &r);
