#ifndef GOLD_H
#define GOLD_H
#include <memory>
class Dragon;

struct loc
{
    int x;
    int y;
};


class Gold {
    loc cord;
virtual int getVal() = 0;
    loc getLoc();
};

class DragonHoard :public Gold {
  //  std::shared_ptr<Dragon> drg;
virtual int getVal() override;
};

class SmallHoard :public Gold {
virtual int getVal() override;

};

class Normal :public Gold {
virtual int getVal() override;

};

#endif // !GOLD_H
