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

class Player :public Character {
public:
	void 
	virtual void attack(Human& human);
	virtual void attack(Dwarf& dwarf);
	virtual void attack(Elf& elf);
	virtual void attack(Orcs& orcs);
	virtual void attack(Merchant& merchant);
	virtual void attack(Dragon& dragon);
	virtual void attack(Halfling& halfling);
	virtual void beAttackedBy(Enemy& e);
};

class Shade :public Player {
public:
	Shade();
};

class Drow :public Player {
public:
	Drow();
};

class Vampire :public Player {
public:
	Vampire();
};

class Troll :public Player {
public:
	Troll();
};

class Goblin :public Player {
public:
	Goblin();
};

#endif // !PLAYER_H

// halulu
