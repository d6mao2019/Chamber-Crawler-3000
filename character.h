#ifndef CHARACTER_H
#define CHARACTER_H
#include "floor.h"
enum class Direction;
#include <memory>
#include <iostream>

class Character
// invariants: all integer data fields are all non-negative.
{
	// current health point.
	double HP;
	// maximum health point.
	const double MaxHP;
	//  attack.
	double Atk;
	//  defense.
	double Def;
	// the amount of gold holding.
	int gold;
	// location on the floor.
	int row, col;

protected:
	// the floor. when an enemy is slain by the player, the enemy notifies floor.
	Floor *floor;

public:
	// constructor.
	Character(double MaxHP, double HP, double Atk, double Def,
			  int gold, int row, int col, Floor *floor);

	double getHP() const;
	double getMaxHP() const;
	double getAtk() const;
	double getDef() const;
	virtual int getGold() const; // overrided by Dragon class.
	int getRow() const;
	int getCol() const;

	void setHP(double new_HP);
	void setAtk(double new_atk);
	void setDef(double new_def);
	void setGold(int new_gold);
	void setLocation(int new_row, int new_col);
	void setFloor(Floor *floor);
	virtual void move(Direction direction);
};
#endif // !CHARACTER_H
