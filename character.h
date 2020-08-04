#ifndef CHARACTER_H
#define CHARACTER_H
#include "floor.h"
#include <memory>

class Character {
	// invariants: HP cannot drop below zero.
	//             Atk and Def should be non-negative integers and should not be modified.

	// current health point.
	int HP;
	// base attack.
	int Atk;
	// base defense.
	int Def;
	// the amount of gold holding.
	int gold;
	// position on the floor.
	int row, col;
	// the floor. when an enemy is slain by the player, the enemy notifies floor.
	Floor* floor;
public:
	virtual int getHP() const;// needs to be overrided by Potion objects.
	virtual int getAtk() const;// needs to be overrided by Potion objects.
	virtual int getDef() const;// needs to be overrided by Potion objects.
	int getGold() const;
	void setHP(int new_HP);
	// calculates the damage caused by this to other.
	int calcDamageTo(const Character& other) const;
};

#endif // !CHARACTER_H
