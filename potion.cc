#include "potion.h"
#include "player.h"

Potion::Potion(double effect, int row, int col)
    : Item{'P', row, col}, effect{effect} {}
Potion::~Potion() {}
double Potion::getEffect() const { return effect; }

///////////////////////////////////////////////////////////////////////////////
/* AtkBoost Class */
AtkBoost::AtkBoost(int row, int col)
    : Potion{5, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* AtkWound Class */
AtkWound::AtkWound(int row, int col)
    : Potion{-5, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* DefBoost Class */
DefBoost::DefBoost(int row, int col)
    : Potion{5, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* DefWound Class */
DefWound::DefWound(int row, int col)
    : Potion{-5, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* HPBoost Class */
HPBoost::HPBoost(int row, int col)
    : Potion{10, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* HPWound Class */
HPWound::HPWound(int row, int col)
    : Potion{-10, row, col} {}
