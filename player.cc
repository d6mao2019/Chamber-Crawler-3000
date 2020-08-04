#include "player.h"
#include "enemy.h"

void Player::beAttackedBy(Enemy& e) { e.attack(*this); }

void Player::attack(Dwarf& dwarf) {
	int damage = calcDamageTo(dwarf);
	int new_HP = dwarf.getHP() - damage;
	dwarf.setHP(new_HP);
	setHP(getHP() - 5);
}
