#ifndef CHARACTER_H
#define CHARACTER_H
#include "floor.h"
#include <memory>
#include <iostream>

enum class Direction
{
	no,
	so,
	we,
	ea,
	nw,
	ne,
	sw,
	se
};
std::istream &operator>>(std::istream &in, Direction direction);

class Character
// invariants: all integer data fields are all non-negative.
{
	const int MaxHP;
	// current health point.
	int HP;
	// base attack.
	const int Atk;
	// base defense.
	const int Def;
	// the amount of gold holding.
	int gold;
	// position on the floor.
	int row, col;

protected:
	// the floor. when an enemy is slain by the player, the enemy notifies floor.
	Floor *floor;

public:
	// constructor.
	Character(int MaxHP, int HP, int Atk, int Def, int gold, int row, int col);

	virtual int getHP() const;	// needs to be overrided by Potion objects.
	virtual int getAtk() const; // needs to be overrided by Potion objects.
	virtual int getDef() const; // needs to be overrided by Potion objects.
	int getGold() const;
	int getRow() const;
	int getCol() const;

	void setHP(int new_HP);
	void setGold(int new_gold);
	void move(Direction direction);
	/*
	// calculates the damage caused by this to other.
	int calcDamageTo(const Character &other) const;
	*/
};

bool adjacent(Character &c1, Character &c2);

#endif // !CHARACTER_H
