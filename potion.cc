#include "potion.h"

Potion::Potion(int effect, int scaling, int row, int col)
    : effect{effect}, scaling{scaling}, row{row}, col{col} {}

double Potion::getHP() const { return player->getHP(); }
double Potion::getAtk() const { return player->getAtk() + effect * scaling; }
double Potion::getDef() const { return player->getDef() + effect * scaling; }
