#ifndef GOLD_H
#define GOLD_H
#include <memory>
#include "item.h"

class Gold : public Item
{
    const int value;
    int row, col;

public:
    Gold(int value, int row, int col);
    virtual bool canBepickedup() const;
    int getVal() const;
};

class SmallHoard : public Gold
{
public:
    SmallHoard(int row, int col);
};

class Normal : public Gold
{
public:
    Normal(int row, int col);
};

class MerchantHoard : public Gold
{
public:
    MerchantHoard(int row, int col);
};

class DragonHoard : public Gold
{
    bool canPickUp = 0;

public:
    DragonHoard(int row, int col);
    virtual bool canBepickedup() const override;
};

#endif // !GOLD_H
