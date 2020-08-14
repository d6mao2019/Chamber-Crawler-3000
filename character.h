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
	const double MaxHP;
	// current health point.
	double HP;
	// base attack.
	const double Atk; //感觉这块不要const，之后要改的吧。还是decorator会要这个是const，明天说一下
	// base defense.
	const double Def;
	// the amount of gold holding.
	int gold;
	// position on the floor.
	int row, col;

protected:
	// the floor. when an enemy is slain by the player, the enemy notifies floor.
	Floor *floor;

public:
	// constructor.
	Character(double MaxHP, double HP, double Atk, double Def, int gold, int row, int col);

	virtual int getHP() const;	// needs to be overrided by Potion objects.
	virtual int getAtk() const; // needs to be overrided by Potion objects.
	virtual int getDef() const; // needs to be overrided by Potion objects.
	int getMaxHP() const;
	int getGold() const;
	int getRow() const;
	int getCol() const;

	void setHP(int new_HP);
	void setGold(int new_gold);
	virtual void move(Direction direction);
};

#endif // !CHARACTER_H
