#ifndef GOLD_H
#define GOLD_H
#include "item.h"
#include <memory>

class Gold : public Item
{
private:
    const int value;

public:
    Gold(int value, int row, int col);
    virtual ~Gold();
    int getVal() const;
    virtual bool canBepickedup() const; // override by DragonHoard class.
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
    void setPickUp(bool new_val);
};

#endif // !GOLD_H
