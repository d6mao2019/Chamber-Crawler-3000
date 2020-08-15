#include "enemy.h"
#include "player.h"
#include "gold.h"
#include <cmath>

Enemy::Enemy(double MaxHP, double HP, double Atk, double Def, int gold, int row, int col)
	: Character{MaxHP, HP, Atk, Def, gold, row, col} {}
Enemy::~Enemy() {}

bool Enemy::adjacent(const Player &p) const
{
	int dist_square = pow(this->getRow() - p.getRow(), 2) + pow(this->getCol() - p.getCol(), 2);
	return dist_square == 1 || dist_square == 2;
}

template <typename PlayerType>
void common_attack(Enemy *e, PlayerType &p)
{
	if (e->adjacent(p))
	{
		double atk = e->getAtk();
		double def = p.getDef();
		double damage = 100 / (100 + def) * atk;
		p.setHP(p.getHP() - damage);
	}
}
void Enemy::attack(Shade &shade) { common_attack<Shade>(this, shade); }
void Enemy::attack(Drow &drow) { common_attack<Drow>(this, drow); }
void Enemy::attack(Vampire &vampire) { common_attack<Vampire>(this, vampire); }
void Enemy::attack(Troll &troll) { common_attack<Troll>(this, troll); }
void Enemy::attack(Goblin &goblin) { common_attack<Goblin>(this, goblin); }

void Enemy::notify() { floor->beNotifiedBy(*this); }

bool Enemy::operator==(Enemy &other)
{
	return this->getRow() == other.getRow() && this->getCol() == other.getCol();
}

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
	if (e->adjacent(p))
	{
		double atk = e->getAtk();
		double def = p.getDef();
		double damage = 100 / (100 + def) * atk;
		damage *= 2;
		p.setHP(p.getHP() - damage);
	}
}
void Elf::attack(Shade &shade) { elf_attack<Shade>(this, shade); }
void Elf::attack(Vampire &vampire) { elf_attack<Vampire>(this, vampire); }
void Elf::attack(Troll &troll) { elf_attack<Troll>(this, troll); }
void Elf::attack(Goblin &goblin) { elf_attack<Goblin>(this, goblin); }

///////////////////////////////////////////////////////////////////////////////
/* Orc Class */ /* 1 attack override(s). */
Orc::Orc(int row, int col)
	: Enemy{180, 180, 30, 25, 0, row, col} {}
void Orc::beAttackedBy(Player &p) { p.attack(*this); }

void Orc::attack(Goblin &goblin)
{
	if (adjacent(goblin))
	{
		double atk = getAtk();
		double def = goblin.getDef();
		double damage = 1.5 * (100 / (100 + def) * atk);
		goblin.setHP(goblin.getHP() - damage);
	}
}

///////////////////////////////////////////////////////////////////////////////
/* Merchant Class */ /* 5 attack override(s) */
bool Merchant::neutral = true;
Merchant::Merchant(int row, int col)
	: Enemy{30, 30, 70, 5, 0, row, col} {}
void Merchant::beAttackedBy(Player &p) { p.attack(*this); }

bool Merchant::getHostility() const { return neutral; }

template <typename PlayerType>
void merchant_attack(Merchant *e, PlayerType &p)
{
	if (!e->getHostility())
		common_attack<PlayerType>(e, p);
}
void Merchant::attack(Shade &shade) { merchant_attack<Shade>(this, shade); }
void Merchant::attack(Drow &drow) { merchant_attack<Drow>(this, drow); }
void Merchant::attack(Vampire &vampire) { merchant_attack<Vampire>(this, vampire); }
void Merchant::attack(Troll &troll) { merchant_attack<Troll>(this, troll); }
void Merchant::attack(Goblin &goblin) { merchant_attack<Goblin>(this, goblin); }

///////////////////////////////////////////////////////////////////////////////
/* Dragon Class */ /* 0 attack override(s) */
Dragon::Dragon(int row, int col, std::shared_ptr<Gold> hoard)
	: Enemy{150, 150, 20, 20, 0, row, col}, hoard{hoard} {}
void Dragon::beAttackedBy(Player &p) { p.attack(*this); }

bool Dragon::adjacent(const Player &other) const
{
	int dist1 = pow(this->getRow() - other.getRow(), 2) + pow(this->getCol() - other.getCol(), 2);
	int dist2 = pow(hoard->getRow() - other.getRow(), 2) + pow(hoard->getCol() - other.getCol(), 2);
	return dist1 == 1 || dist1 == 2 || dist2 == 1 || dist2 == 2;
}

void Dragon::move(Direction direction) { return; } // does nothing since Dragons are stationary.

///////////////////////////////////////////////////////////////////////////////
/* Halfling Class */ /* 0 attack override(s) */
Halfling::Halfling(int row, int col)
	: Enemy{100, 100, 15, 20, 0, row, col} {}
void Halfling::beAttackedBy(Player &p) { p.attack(*this); }
