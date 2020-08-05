#ifndef GOLD_H
#define GOLD_H
#include <memory>
class Dragon;

class Gold
{
    int value;
    int row, col;

public:
    int getVal() const;
    int getRow() const;
    int getCol() const;
};

class DragonHoard : public Gold
{
    //  std::shared_ptr<Dragon> drg;
};

class SmallHoard : public Gold
{
};

class Normal : public Gold
{
};

#endif // !GOLD_H
