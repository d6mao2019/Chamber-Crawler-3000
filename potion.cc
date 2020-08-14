#include "potion.h"
#include "player.h"

Potion::Potion(int effect, int scaling, int row, int col)
    : effect{effect}, scaling{scaling}, row{row}, col{col} {}

double Potion::getHP() const { return player->getHP(); }
double Potion::getAtk() const { return player->getAtk() + effect * scaling; }
double Potion::getDef() const { return player->getDef() + effect * scaling; }

///////////////////////////////////////////////////////////////////////////////
/* AtkBoost Class */
AtkBoost::AtkBoost(int row, int col, std::shared_ptr<Player> p)
    : Player { 0, 0, 0, 0, 0, row, col, p->get }

///////////////////////////////////////////////////////////////////////////////
/* DefBoost Class */

///////////////////////////////////////////////////////////////////////////////
/* AtkWound Class */

///////////////////////////////////////////////////////////////////////////////
/* DefWound Class */
