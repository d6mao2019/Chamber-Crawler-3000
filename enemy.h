#ifndef ENEMY_H
#define ENEMY_H
#include "character.h"
class Player;
class Shade;
class Drow;
class Vampire;
class Troll;
class Goblin;

class Enemy :public Character {
public:
	virtual void attack(Shade& shade);
	virtual void attack(Drow& drow);
	virtual void attack(Vampire& vampire);
	virtual void attack(Troll& troll);
	virtual void attack(Goblin& goblin);
	virtual void beAttackedBy(Player& p);
};

class Human :public Enemy {
public:
	Human();
};

class Dwarf :public Enemy {
public:
	Dwarf();
};

class Elf :public Enemy {
public:
	Elf();
};

class Orcs :public Enemy {
public:
	Orcs();
};

class Merchant :public Enemy {
	static bool neutral;
public:
	Merchant();
};

class Dragon :public Enemy {
public:
	Dragon();
};

class Halfling :public Enemy {
public:
	Halfling();
};

#endif // !ENEMY_H
