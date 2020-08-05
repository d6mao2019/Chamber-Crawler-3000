#include "character.h"
#include <cmath>

int Character::getHP() const { return HP; }
int Character::getAtk() const { return Atk; }
int Character::getDef() const { return Def; }
int Character::getGold() const { return gold; }

void Character::setHP(int new_HP) { HP = new_HP; }

void Character::move(int row_change, int col_change)
{
	row += row_change;
	col += col_change;
}

int Character::calcDamageTo(const Character &other) const
{
	double atk = getAtk();
	double def = other.getDef();
	int damage = ceil(100 / (100 + def) * atk);
	return damage;
}
