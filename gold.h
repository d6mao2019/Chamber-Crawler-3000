#ifndef GOLD_H
#define GOLD_H
#include <memory>
class Dragon;

class Gold
{
    const int value;
    int row, col;

public:
    Gold(int value, int row, int col);
    int getVal() const;
    int getRow() const;
    int getCol() const;
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
public:
    DragonHoard(int row, int col);
};

#endif // !GOLD_H
