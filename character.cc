#include "character.h"
#include <cmath>

void Character::setHP(int new_HP) { HP = new_HP; }

int Character::getHP() const { return HP; }
int Character::getAtk() const { return Atk; }
int Character::getDef() const { return Def; }

int Character::calcDamageTo(const Character& other) {
	double atk = getAtk();
	double def = other.getDef();
	int damage = ceil(100 / (100 + def) * atk);
	return damage;
}
