#include "potion.h"
#include "player.h"

Potion::Potion(int row, int col)
    : Item{'P', row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* AtkBoost Class */
AtkBoost::AtkBoost(int row, int col)
    : Potion{row, col} {}
void AtkBoost::consume(Player &pl) { pl.setAtk(boost * pl.getScal() + pl.getAtk()); }

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
void HPBoost::consume(Player &pl) { pl.setHP(pl.getHP() + hp * pl.getScal()); }

///////////////////////////////////////////////////////////////////////////////
/* HPWound Class */
HPWound::HPWound(int row, int col)
    : Potion{row, col} {}
void HPWound::consume(Player &pl) { pl.setHP(pl.getHP() - hp * pl.getScal()); }
