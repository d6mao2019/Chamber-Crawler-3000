#include "player.h"
#include "enemy.h"

void attack(Dwarf &dwarf);
void attack(Elf &elf);
void attack(Orcs &orcs);
void attack(Merchant &merchant);
void attack(Dragon &dragon);
void attack(Halfling &halfling);

void Player::beAttackedBy(Enemy &e) { e.attack(*this); }

void Player::attack(Dwarf &dwarf)
{
	int damage = calcDamageTo(dwarf);
	int new_HP = dwarf.getHP() - damage;
	dwarf.setHP(new_HP);
	setHP(getHP() - 5);
}
