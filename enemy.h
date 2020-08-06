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
	Enemy(int HP, int Atk, int Def, int gold, int row, int col);
	virtual void attack(Shade &shade);
	virtual void attack(Drow &drow);
	virtual void attack(Vampire &vampire);
	virtual void attack(Troll &troll);
	virtual void attack(Goblin &goblin);
	virtual void beAttackedBy(Player &p) = 0;
	void notify(); // notify the floor when slain.
};

class Human : public Enemy
{
public:
	Human(int row, int col);
	virtual void beAttackedBy(Player &p) override;
};

class Dwarf : public Enemy
{
public:
	Dwarf(int row, int col);
	virtual void beAttackedBy(Player &p) override;
};

class Elf : public Enemy
// gets two attacks against every race except drow
{
public:
	Elf(int row, int col);
	virtual void beAttackedBy(Player &p) override;

	virtual void attack(Shade &shade) override;
	// only drow do not need to override.
	virtual void attack(Vampire &vampire) override;
	virtual void attack(Troll &troll) override;
	virtual void attack(Goblin &goblin) override;
};

class Orcs : public Enemy
{
public:
	Orcs(int row, int col);
	virtual void beAttackedBy(Player &p) override;
};

class Merchant : public Enemy
{
	static bool neutral;

public:
	Merchant(int row, int col);
	virtual void beAttackedBy(Player &p) override;
};

class Dragon : public Enemy
{
	std::shared_ptr<Gold> drgold;

public:
	Dragon(int row, int col);
	virtual void beAttackedBy(Player &p) override;
};

class Halfling : public Enemy
{
public:
	Halfling(int row, int col);
	virtual void beAttackedBy(Player &p) override;
};

#endif // !ENEMY_H
