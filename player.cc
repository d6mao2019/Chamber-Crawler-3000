#include "player.h"
#include "enemy.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include "item.h"

Player::Player(double MaxHP, double HP, double Atk, double Def,
			   int gold, int row, int col, double scaling, Floor *floor)
	: Character{MaxHP, HP, Atk, Def, gold, row, col, floor},
	  scaling{scaling}, origAtk{Atk}, origDef{Def} {}
Player::~Player() {}

bool Player::adjacent(const Enemy &e) const
{
	int dist_square = pow(this->getRow() - e.getRow(), 2) + pow(this->getCol() - e.getCol(), 2);
	return dist_square == 1 || dist_square == 2;
}

bool Player::adjacent(const Item &i) const
{
	int dist_square = pow(this->getRow() - i.getRow(), 2) + pow(this->getCol() - i.getCol(), 2);
	return dist_square == 1 || dist_square == 2;
}

char Player::getPrev() const { return prev; }
double Player::getScal() const { return scaling; }

void Player::setPrev(char p)
{
	if (p != '+' && p != '#')
	{
		p = '.';
	}
	prev = p;
}

std::ostream &operator<<(std::ostream &out, const Player &p)
{
	out << "HP: " << p.getHP() << std::endl;
	out << "Atk: " << p.getAtk() << std::endl;
	out << "Def: " << p.getDef() << std::endl;
	return out;
}

template <typename EnemyType>
void common_attack(Player *p, EnemyType &e, int miss_combat_chance)
{
	if (p->adjacent(e))
	{
		bool miss = (rand() % 100 < miss_combat_chance);
		if (miss)
			return;
		double atk = p->getAtk();
		double def = e.getDef();
		double damage = 100 / (100 + def) * atk;
		if (e.getHP() > damage)
			e.setHP(e.getHP() - damage);
		else // slain.
		{
			e.notify();
			p->setGold(p->getGold() + e.getGold());
		}
	}
	else
		throw std::runtime_error{"Error: trying to attack non-adjacent target."};
}
void Player::attack(Human &human) { common_attack<Human>(this, human, 0); }
void Player::attack(Dwarf &dwarf) { common_attack<Dwarf>(this, dwarf, 0); }
void Player::attack(Elf &elf) { common_attack<Elf>(this, elf, 0); }
void Player::attack(Orc &orc) { common_attack<Orc>(this, orc, 0); }
void Player::attack(Merchant &merchant) { common_attack<Merchant>(this, merchant, 0); }
void Player::attack(Dragon &dragon) { common_attack<Dragon>(this, dragon, 0); }
void Player::attack(Halfling &halfling) { common_attack<Halfling>(this, halfling, 50); }

void Player::restore()
{
	prev = '.';
	setAtk(origAtk);
	setDef(origDef);
}

///////////////////////////////////////////////////////////////////////////////
/* Shade Class */ /* 0 attack override(s) */
Shade::Shade(int row, int col)
	: Player{10000, 10000, 10000, 10000, 0, row, col, 1.0, nullptr} {}
void Shade::beAttackedBy(Enemy &e) { e.attack(*this); }
std::string Shade::getRace() { return "Shade"; }

///////////////////////////////////////////////////////////////////////////////
/* Drow Class */ /* 0 attack override(s) */
Drow::Drow(int row, int col)
	: Player{150, 150, 25, 15, 0, row, col, 1.5, nullptr} {}
void Drow::beAttackedBy(Enemy &e) { e.attack(*this); }
std::string Drow::getRace() { return "Drow"; }

///////////////////////////////////////////////////////////////////////////////
/* Vampire Class */ /* 7 attack override(s) */
Vampire::Vampire(int row, int col)
	: Player{INT32_MAX, 50, 35, 25, 0, row, col, 1.0, nullptr} {}
void Vampire::beAttackedBy(Enemy &e) { e.attack(*this); }
std::string Vampire::getRace() { return "Vampire"; }

template <typename EnemyType>
void vampire_attack_gain_HP(Player *p, EnemyType &e, int miss_combat_chance)
{
	common_attack<EnemyType>(p, e, miss_combat_chance);
	p->setHP(p->getHP() + 5);
}
template <typename EnemyType>
void vampire_attack_lose_HP(Player *p, EnemyType &e, int miss_combat_chance)
{
	common_attack<EnemyType>(p, e, miss_combat_chance);
	p->setHP(p->getHP() - 5);
}
void Vampire::attack(Human &human) { vampire_attack_gain_HP<Human>(this, human, 0); }
void Vampire::attack(Dwarf &dwarf) { vampire_attack_lose_HP<Dwarf>(this, dwarf, 0); }
void Vampire::attack(Elf &elf) { vampire_attack_gain_HP<Elf>(this, elf, 0); }
void Vampire::attack(Orc &orc) { vampire_attack_gain_HP<Orc>(this, orc, 0); }
void Vampire::attack(Merchant &merchant) { vampire_attack_gain_HP<Merchant>(this, merchant, 0); }
void Vampire::attack(Dragon &dragon) { vampire_attack_gain_HP<Dragon>(this, dragon, 0); }
void Vampire::attack(Halfling &halfling) { vampire_attack_gain_HP<Halfling>(this, halfling, 50); }

///////////////////////////////////////////////////////////////////////////////
/* Troll Class */ /* 0 attack override(s) */
Troll::Troll(int row, int col)
	: Player{120, 120, 25, 15, 0, row, col, 1.0, nullptr} {}
void Troll::beAttackedBy(Enemy &e) { e.attack(*this); }
std::string Troll::getRace() { return "Troll"; }

///////////////////////////////////////////////////////////////////////////////
/* Goblin Class */ /* 7 attack override(s) */
Goblin::Goblin(int row, int col)
	: Player{110, 110, 15, 20, 0, row, col, 1.0, nullptr} {}
void Goblin::beAttackedBy(Enemy &e) { e.attack(*this); }
std::string Goblin ::getRace() { return "Goblin"; }

template <typename EnemyType>
void goblin_attack(Player *p, EnemyType &e, int miss_combat_chance)
{
	if (p->adjacent(e))
	{
		bool miss = (rand() % 100 < miss_combat_chance);
		if (miss)
			return;
		double atk = p->getAtk();
		double def = e.getDef();
		double damage = 100 / (100 + def) * atk;
		if (e.getHP() > damage)
			e.setHP(e.getHP() - damage);
		else
		{
			e.notify();
			p->setGold(p->getGold() + e.getGold());
			p->setGold(p->getGold() + 5);
		}
	}
	else
		throw std::runtime_error{"Error: trying to attack non-adjacent target."};
}
void Goblin::attack(Human &human) { goblin_attack<Human>(this, human, 0); }
void Goblin::attack(Dwarf &dwarf) { goblin_attack<Dwarf>(this, dwarf, 0); }
void Goblin::attack(Elf &elf) { goblin_attack<Elf>(this, elf, 0); }
void Goblin::attack(Orc &orc) { goblin_attack<Orc>(this, orc, 0); }
void Goblin::attack(Merchant &merchant) { goblin_attack<Merchant>(this, merchant, 0); }
void Goblin::attack(Dragon &dragon) { goblin_attack<Dragon>(this, dragon, 0); }
void Goblin::attack(Halfling &halfling) { goblin_attack<Halfling>(this, halfling, 50); }
