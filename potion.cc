#include "potion.h"
#include "player.h"
#include <cmath>

Potion::Potion(int row, int col)
    : Item{'P', row, col} {}
Potion::~Potion() {}

///////////////////////////////////////////////////////////////////////////////
/* AtkBoost Class */
AtkBoost::AtkBoost(int row, int col)
    : Potion{row, col} {}
void AtkBoost::consume(Player &pl) { pl.setAtk(pl.getAtk() + boost * pl.getScal()); }

///////////////////////////////////////////////////////////////////////////////
/* AtkWound Class */
AtkWound::AtkWound(int row, int col)
    : Potion{row, col} {}
void AtkWound::consume(Player &pl) { pl.setAtk(pl.getAtk() - wound * pl.getScal()); }

///////////////////////////////////////////////////////////////////////////////
/* DefBoost Class */
DefBoost::DefBoost(int row, int col)
    : Potion{row, col} {}
void DefBoost::consume(Player &pl) { pl.setDef(pl.getDef() + boost * pl.getScal()); }

///////////////////////////////////////////////////////////////////////////////
/* DefWound Class */
DefWound::DefWound(int row, int col)
    : Potion{row, col} {}
void DefWound::consume(Player &pl) { pl.setDef(pl.getDef() - wound * pl.getScal()); }

///////////////////////////////////////////////////////////////////////////////
/* HPBoost Class */
HPBoost::HPBoost(int row, int col)
    : Potion{row, col} {}
void HPBoost::consume(Player &pl) { pl.setHP(pl.getHP() + restore * pl.getScal()); }

///////////////////////////////////////////////////////////////////////////////
/* HPWound Class */
HPWound::HPWound(int row, int col)
    : Potion{row, col} {}
void HPWound::consume(Player &pl) { pl.setHP(pl.getHP() - poison * pl.getScal()); }
