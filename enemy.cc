#include "enemy.h"
#include "player.h"

Enemy::Enemy(int HP, int Atk, int Def, int gold, int row, int col)
	: Character{HP, Atk, Def, gold, row, col} {}

template <typename PlayerType>
void common_attack(Enemy *e, PlayerType &p)
{
	int damage = e->calcDamageTo(p);
	if (p.getHP() > damage)
		p.setHP(p.getHP() - damage);
	else // player got killed. game over.
		 // don't know what to do yet.
}
void Enemy::attack(Shade &shade) { common_attack<Shade>(this, shade); }
void Enemy::attack(Drow &drow) { common_attack<Drow>(this, drow); }
void Enemy::attack(Vampire &vampire) { common_attack<Vampire>(this, vampire); }
void Enemy::attack(Troll &troll) { common_attack<Troll>(this, troll); }
void Enemy::attack(Goblin &goblin) { common_attack<Goblin>(this, goblin); }

void Enemy::notify() { floor->beNotifiedBy(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Human Class */
Human::Human(int row, int col)
	: Enemy{140, 20, 20, 4, row, col} {}

void Human::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Dwarf Class */
Dwarf::Dwarf(int row, int col)
	: Enemy{100, 20, 30, 0, row, col} {}

void Dwarf::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Elf Class */
Elf::Elf(int row, int col)
	: Enemy{140, 30, 10, 0, row, col} {}

void Elf::beAttackedBy(Player &p) { p.attack(*this); }

template <typename PlayerType>
void elf_attack(Enemy *e, PlayerType &p)
{
	int damage = e->calcDamageTo(p);
	damage *= 2;
	if (p.getHP() > damage)
		p.setHP(p.getHP() - damage);
	else // player got killed. game over.
		 // don't know what to do yet.
}
void Elf::attack(Shade &shade) { elf_attack<Shade>(this, shade); }

void Elf::attack(Vampire &vampire)
{
}
///////////////////////////////////////////////////////////////////////////////
/* Orcs Class */
Orcs::Orcs(int row, int col)
	: Enemy{180, 30, 25, 0, row, col}
{
}

void Orcs::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Merchant Class */
Merchant::Merchant(int row, int col)
	: Enemy{30, 70, 5, 0, row, col} {}

void Merchant::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Dragon Class */
Dragon::Dragon(int row, int col)
	: Enemy{150, 20, 20, 0, row, col} {}

void Dragon::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Halfling Class */
Halfling::Halfling(int row, int col)
	: Enemy{100, 15, 20, 0, row, col} {}

void Halfling::beAttackedBy(Player &p) { p.attack(*this); }
