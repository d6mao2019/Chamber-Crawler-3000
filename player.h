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
	virtual void attack(Human& human) = 0;
	virtual void attack(Dwarf& dwarf) = 0;
	virtual void attack(Elf& elf) = 0;
	virtual void attack(Orcs& orcs) = 0;
	virtual void attack(Merchant& merchant) = 0;
	virtual void attack(Dragon& dragon) = 0;
	virtual void attack(Halfling& halfling) = 0;
	virtual void beAttackedBy(Enemy& e);
};

class Shade :public Player {
public:
	Shade();
	virtual void attack(Human& human) override;
	virtual void attack(Dwarf& dwarf) override;
	virtual void attack(Elf& elf) override;
	virtual void attack(Orcs& orcs) override;
	virtual void attack(Merchant& merchant) override;
	virtual void attack(Dragon& dragon) override;
	virtual void attack(Halfling& halfling) override;
};

class Drow :public Player {
public:
	Drow();
	virtual void attack(Human& human) override;
	virtual void attack(Dwarf& dwarf) override;
	virtual void attack(Elf& elf) override;
	virtual void attack(Orcs& orcs) override;
	virtual void attack(Merchant& merchant) override;
	virtual void attack(Dragon& dragon) override;
	virtual void attack(Halfling& halfling) override;
};

class Vampire :public Player {
public:
	Vampire();
	virtual void attack(Human& human) override;
	virtual void attack(Dwarf& dwarf) override;
	virtual void attack(Elf& elf) override;
	virtual void attack(Orcs& orcs) override;
	virtual void attack(Merchant& merchant) override;
	virtual void attack(Dragon& dragon) override;
	virtual void attack(Halfling& halfling) override;
};

class Troll :public Player {
public:
	Troll();
	virtual void attack(Human& human) override;
	virtual void attack(Dwarf& dwarf) override;
	virtual void attack(Elf& elf) override;
	virtual void attack(Orcs& orcs) override;
	virtual void attack(Merchant& merchant) override;
	virtual void attack(Dragon& dragon) override;
	virtual void attack(Halfling& halfling) override;
};

class Goblin :public Player {
public:
	Goblin();
	virtual void attack(Human& human) override;
	virtual void attack(Dwarf& dwarf) override;
	virtual void attack(Elf& elf) override;
	virtual void attack(Orcs& orcs) override;
	virtual void attack(Merchant& merchant) override;
	virtual void attack(Dragon& dragon) override;
	virtual void attack(Halfling& halfling) override;
};

#endif // !PLAYER_H
