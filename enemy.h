#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Enemy : public Character
{
public:
	// Enemy constructor.
	Enemy(int MaxHP, int HP, int Atk, int Def, int gold, int row, int col);

	virtual bool adjacent(Player &other);
	virtual void attack(Shade &shade);
	virtual void attack(Drow &drow);
	virtual void attack(Vampire &vampire);
	virtual void attack(Troll &troll);
	virtual void attack(Goblin &goblin);
	virtual void beAttackedBy(Player &p) = 0;
	void notify(); // notify the floor when slain.

	bool operator==(Enemy &other); // Enemy comparison by location on floor.
};

class Human : public Enemy
// drops 2 normal piles of gold.
{
public:
	Human(int row, int col);
	virtual void beAttackedBy(Player &p) override;
	// 0 attack override(s).
};

class Dwarf : public Enemy
// Vampires are allergic to dwarves and lose 5 HP rather than gain.
{
public:
	Dwarf(int row, int col);
	virtual void beAttackedBy(Player &p) override;
	// 0 attack override(s).
};

class Elf : public Enemy
// gets two attacks against every race except drow.
{
public:
	Elf(int row, int col);
	virtual void beAttackedBy(Player &p) override;
	// 4 attack override(s).
	virtual void attack(Shade &shade) override;
	virtual void attack(Vampire &vampire) override;
	virtual void attack(Troll &troll) override;
	virtual void attack(Goblin &goblin) override;
};

class Orc : public Enemy
// does 50% more damage to goblins.
{
public:
	Orc(int row, int col);
	virtual void beAttackedBy(Player &p) override;
	// 1 attack override(s).
	virtual void attack(Goblin &goblin) override;
};

class Merchant : public Enemy
{
	static bool neutral;

public:
	Merchant(int row, int col);
	virtual void beAttackedBy(Player &p) override;
	// 0 attack override(s).
};

class Dragon : public Enemy
// always guards a treasure hoard.
{
	std::shared_ptr<Gold> hoard;

public:
	Dragon(int row, int col);
	virtual bool adjacent(Player &other) override;
	virtual void beAttackedBy(Player &p) override;
	// 0 attack override(s).
};

class Halfling : public Enemy
// has a 50% chance to cause the player character to miss in combat.
{
public:
	Halfling(int row, int col);
	virtual void beAttackedBy(Player &p) override;
	// 0 attack override(s).
};

#endif // !ENEMY_H
