#include "player.h"
#include "enemy.h"
#include <cmath>

Player::Player(int HP, int Atk, int Def, int gold, int row, int col)
	: Character{HP, Atk, Def, gold, row, col} {}

template <typename EnemyType>
void common_attack(Player *p, EnemyType &e)
{
	double atk = p->getAtk();
	double def = e.getDef();
	int damage = ceil(100 / (100 + def) * atk);
	if (e.getHP() > damage)
		e.setHP(e.getHP() - damage);
	else
		e.notify();
}
void Player::attack(Human &human) { common_attack<Human>(this, human); }
void Player::attack(Dwarf &dwarf) { common_attack<Dwarf>(this, dwarf); }
void Player::attack(Elf &elf) { common_attack<Elf>(this, elf); }
void Player::attack(Orcs &orcs) { common_attack<Orcs>(this, orcs); }
void Player::attack(Merchant &merchant) { common_attack<Merchant>(this, merchant); }
void Player::attack(Dragon &dragon) { common_attack<Dragon>(this, dragon); }
void Player::attack(Halfling &halfling) { common_attack<Halfling>(this, halfling); }

///////////////////////////////////////////////////////////////////////////////
/* Shade Class */ /* 0 attack override(s) */
Shade::Shade(int row, int col)
	: Player{125, 25, 25, 0, row, col} {}
void Shade::beAttackedBy(Enemy &e) { e.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Drow Class */ /* 0 attack override(s) */
Drow::Drow(int row, int col)
	: Player{150, 25, 15, 0, row, col} {}
void Drow::beAttackedBy(Enemy &e) { e.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Vampire Class */ /* 7 attack override(s) */
Vampire::Vampire(int row, int col)
	: Player{50, 35, 25, 0, row, col} {}
void Vampire::beAttackedBy(Enemy &e) { e.attack(*this); }

template <typename EnemyType>
void vampire_attack_gain_HP(Player *p, EnemyType &e)
{
	common_attack<EnemyType>(p, e);
	p->setHP(p->getHP() + 5);
}
template <typename EnemyType>
void vampire_attack_lose_HP(Player *p, EnemyType &e)
{
	common_attack<EnemyType>(p, e);
	p->setHP(p->getHP() - 5);
}
void Vampire::attack(Human &human) { vampire_attack_gain_HP<Human>(this, human); }
void Vampire::attack(Dwarf &dwarf) { vampire_attack_lose_HP<Dwarf>(this, dwarf); }
void Vampire::attack(Elf &elf) { vampire_attack_gain_HP<Elf>(this, elf); }
void Vampire::attack(Orcs &orcs) { vampire_attack_gain_HP<Orcs>(this, orcs); }
void Vampire::attack(Merchant &merchant) { vampire_attack_gain_HP<Merchant>(this, merchant); }
void Vampire::attack(Dragon &dragon) { vampire_attack_gain_HP<Dragon>(this, dragon); }
void Vampire::attack(Halfling &halfling) { vampire_attack_gain_HP<Halfling>(this, halfling); }

///////////////////////////////////////////////////////////////////////////////
/* Troll Class */ /* 7 attack override(s) */
Troll::Troll(int row, int col)
	: Player{120, 25, 15, 0, row, col} {}
void Troll::beAttackedBy(Enemy &e) { e.attack(*this); }
