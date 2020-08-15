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
std::istream &operator>>(std::istream &in, Direction &direction);

class Character
// invariants: all integer data fields are all non-negative.
{
	const double MaxHP;
	// current health point.
	double HP;
	//  attack.
	double Atk;
	//  defense.
	double Def;
	// the amount of gold holding.
	int gold;
	// position on the floor.
	int row, col;

protected:
	// the floor. when an enemy is slain by the player, the enemy notifies floor.
	Floor *floor;

public:
	// constructor.
	Character(double MaxHP, double HP, double Atk, double Def,
			  int gold, int row, int col, Floor *floor);

	virtual double getHP() const;  // needs to be overrided by Potion objects.
	virtual double getAtk() const; // needs to be overrided by Potion objects.
	virtual double getDef() const; // needs to be overrided by Potion objects.
	double getMaxHP() const;
	int getGold() const;
	int getRow() const;
	int getCol() const;

	void setHP(double new_HP);
	void setAtk(double new_atk);
	void setDef(double new_def);
	void setGold(int new_gold);
	void setLocation(int row, int col);
	void setFloor(Floor *floor);
	virtual void move(Direction direction);
	std::pair<int, int> GetLocAfterMove(Direction d, int row, int col);
};
#endif // !CHARACTER_H
