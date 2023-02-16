#include "BombIterator.h"

BombIterator &BombIterator::operator++()
{
    if (curIndex != refArr.size()) {
        ++curIndex;
    }
    return *this;
}

BombIterator &BombIterator::operator--()
{
    if (curIndex != 0) {
        --curIndex;
    }
    return *this;
}

Bomb *BombIterator::operator*()
{
    return dynamic_cast<Bomb *>(refArr.at(curIndex));
}

bool operator==(const BombConstIterator &l, const BombConstIterator &r)
{
    return l.curIndex == r.curIndex && l.refArr == r.refArr;
}

bool operator!=(const BombConstIterator &l, const BombConstIterator &r)
{
    return !(l == r);
}

BombConstIterator &BombConstIterator::operator++()
{
    if (curIndex != refArr.size()) {
        ++curIndex;
    }
    return *this;
}

BombConstIterator &BombConstIterator::operator--()
{
    if (curIndex != 0) {
        --curIndex;
    }
    return *this;
}

Bomb *BombConstIterator::operator*()
{
    return dynamic_cast<Bomb *>(refArr.at(curIndex));
}
