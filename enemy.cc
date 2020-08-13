#include "enemy.h"
#include "player.h"
#include <cmath>

Enemy::Enemy(int MaxHP, int HP, int Atk, int Def, int gold, int row, int col)
	: Character{MaxHP, HP, Atk, Def, gold, row, col} {}

template <typename PlayerType>
void common_attack(Enemy *e, PlayerType &p)
{
	double atk = e->getAtk();
	double def = p.getDef();
	int damage = ceil(100 / (100 + def) * atk);
	if (p.getHP() > damage)
		p.setHP(p.getHP() - damage);
	else
	{
		// player got killed. game over.
		// don't know what to do yet.
	}
}
void Enemy::attack(Shade &shade) { common_attack<Shade>(this, shade); }
void Enemy::attack(Drow &drow) { common_attack<Drow>(this, drow); }
void Enemy::attack(Vampire &vampire) { common_attack<Vampire>(this, vampire); }
void Enemy::attack(Troll &troll) { common_attack<Troll>(this, troll); }
void Enemy::attack(Goblin &goblin) { common_attack<Goblin>(this, goblin); }

void Enemy::notify() { floor->beNotifiedBy(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Human Class */ /* 0 attack override(s) */
Human::Human(int row, int col)
	: Enemy{140, 140, 20, 20, 4, row, col} {}
void Human::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Dwarf Class */ /* 0 attack override(s) */
Dwarf::Dwarf(int row, int col)
	: Enemy{100, 100, 20, 30, 0, row, col} {}
void Dwarf::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Elf Class */ /* 4 attack override(s). */
Elf::Elf(int row, int col)
	: Enemy{140, 140, 30, 10, 0, row, col} {}
void Elf::beAttackedBy(Player &p) { p.attack(*this); }

template <typename PlayerType>
void elf_attack(Enemy *e, PlayerType &p)
{
	double atk = e->getAtk();
	double def = p.getDef();
	int damage = ceil(100 / (100 + def) * atk);
	damage *= 2;
	if (p.getHP() > damage)
		p.setHP(p.getHP() - damage);
	else
	{
		// player got killed. game over.
		// don't know what to do yet.
	}
}
void Elf::attack(Shade &shade) { elf_attack<Shade>(this, shade); }
void Elf::attack(Vampire &vampire) { elf_attack<Vampire>(this, vampire); }
void Elf::attack(Troll &troll) { elf_attack<Troll>(this, troll); }
void Elf::attack(Goblin &goblin) { elf_attack<Goblin>(this, goblin); }

///////////////////////////////////////////////////////////////////////////////
/* Orcs Class */ /* 1 attack override(s). */
Orcs::Orcs(int row, int col)
	: Enemy{180, 180, 30, 25, 0, row, col} {}
void Orcs::beAttackedBy(Player &p) { p.attack(*this); }

void Orcs::attack(Goblin &goblin)
{
	double atk = getAtk();
	double def = goblin.getDef();
	int damage = ceil(1.5 * (100 / (100 + def) * atk));
	if (goblin.getHP() > damage)
		goblin.setHP(goblin.getHP() - damage);
	else
	{
		// player got killed. game over.
		// don't know what to do yet.
	}
}

///////////////////////////////////////////////////////////////////////////////
/* Merchant Class */ /* 0 attack override(s) */
Merchant::Merchant(int row, int col)
	: Enemy{30, 30, 70, 5, 0, row, col} {}
void Merchant::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Dragon Class */ /* 0 attack override(s) */
Dragon::Dragon(int row, int col)
	: Enemy{150, 150, 20, 20, 0, row, col} {}
void Dragon::beAttackedBy(Player &p) { p.attack(*this); }

///////////////////////////////////////////////////////////////////////////////
/* Halfling Class */ /* 0 attack override(s) */
Halfling::Halfling(int row, int col)
	: Enemy{100, 100, 15, 20, 0, row, col} {}
void Halfling::beAttackedBy(Player &p) { p.attack(*this); }
