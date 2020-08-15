#include "potion.h"
#include "player.h"
#include <cmath>

Potion::Potion(int row, int col)
    : Item{'P', row, col} {}
Potion::~Potion() {}
bool Potion::adjacent(const Player &p) const
{
    int dist_square = pow(getRow() - p.getRow(), 2) + pow(getCol() - p.getCol(), 2);
    return dist_square == 1 || dist_square == 2;
}

///////////////////////////////////////////////////////////////////////////////
/* AtkBoost Class */
AtkBoost::AtkBoost(int row, int col)
    : Potion{row, col} {}
void AtkBoost::consume(Player &pl)
{
    if (adjacent(pl))
        pl.setAtk(boost * pl.getScal() + pl.getAtk());
}

///////////////////////////////////////////////////////////////////////////////
/* AtkWound Class */
AtkWound::AtkWound(int row, int col)
    : Potion{row, col} {}
void AtkWound::consume(Player &pl)
{
    if (adjacent(pl))
        pl.setAtk(pl.getAtk() - wound * pl.getScal());
}

///////////////////////////////////////////////////////////////////////////////
/* DefBoost Class */
DefBoost::DefBoost(int row, int col)
    : Potion{row, col} {}
void DefBoost::consume(Player &pl)
{
    if (adjacent(pl))
        pl.setDef(pl.getDef() + boost * pl.getScal());
}

///////////////////////////////////////////////////////////////////////////////
/* DefWound Class */
DefWound::DefWound(int row, int col)
    : Potion{row, col} {}
void DefWound::consume(Player &pl)
{
    if (adjacent(pl))
        pl.setDef(pl.getDef() - wound * pl.getScal());
}

///////////////////////////////////////////////////////////////////////////////
/* HPBoost Class */
HPBoost::HPBoost(int row, int col)
    : Potion{row, col} {}
void HPBoost::consume(Player &pl)
{
    if (adjacent(pl))
        pl.setHP(pl.getHP() + hp * pl.getScal());
}

///////////////////////////////////////////////////////////////////////////////
/* HPWound Class */
HPWound::HPWound(int row, int col)
    : Potion{row, col} {}
void HPWound::consume(Player &pl)
{
    if (adjacent(pl))
        pl.setHP(pl.getHP() - hp * pl.getScal());
}
