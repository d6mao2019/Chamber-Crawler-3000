#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
class Enemy;
class Human;
class Dwarf;
class Elf;
class Orcs;
class Merchant;
class Dragon;
class Halfling;

class Player : public Character
{
public:
	Player(double MaxHP, double HP, double Atk, double Def, int gold, int row, int col);
	virtual void attack(Human &human);
	virtual void attack(Dwarf &dwarf);
	virtual void attack(Elf &elf);
	virtual void attack(Orcs &orcs);
	virtual void attack(Merchant &merchant);
	virtual void attack(Dragon &dragon);
	virtual void attack(Halfling &halfling);
	virtual void beAttackedBy(Enemy &e) = 0;
};

class Shade : public Player
{
public:
	Shade(int row, int col);
	virtual void beAttackedBy(Enemy &e) override;
	// 0 attack override(s).
};

class Drow : public Player
// all potions have their effect magnified by 1.5.
{
public:
	Drow(int row, int col);
	virtual void beAttackedBy(Enemy &e) override;
	// 0 attack override(s).
};

class Vampire : public Player
// has no maximum HP.
// gains 5 HP every successful attack except for dwarfs.
// loses 5 HP every successful attack on dwarfs.
{
public:
	Vampire(int row, int col);
	virtual void beAttackedBy(Enemy &e) override;
	// 7 attack override(s).
	virtual void attack(Human &human) override;
	virtual void attack(Dwarf &dwarf) override;
	virtual void attack(Elf &elf) override;
	virtual void attack(Orcs &orcs) override;
	virtual void attack(Merchant &merchant) override;
	virtual void attack(Dragon &dragon) override;
	virtual void attack(Halfling &halfling) override;
};

class Troll : public Player
// regains 5 HP every turn (capped at 120).
{
public:
	Troll(int row, int col);
	virtual void beAttackedBy(Enemy &e) override;
	// 0 attack override(s).
};

class Goblin : public Player
// steals 5 gold from every slain enemy.
{
public:
	Goblin(int row, int col);
	virtual void beAttackedBy(Enemy &e) override;
	// 7 attack override(s).
	virtual void attack(Human &human) override;
	virtual void attack(Dwarf &dwarf) override;
	virtual void attack(Elf &elf) override;
	virtual void attack(Orcs &orcs) override;
	virtual void attack(Merchant &merchant) override;
	virtual void attack(Dragon &dragon) override;
	virtual void attack(Halfling &halfling) override;
};

#endif // !PLAYER_H
