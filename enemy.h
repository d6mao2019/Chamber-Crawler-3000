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
	virtual void attack(Shade& shade) = 0;
	virtual void attack(Drow& drow) = 0;
	virtual void attack(Vampire& vampire) = 0;
	virtual void attack(Troll& troll) = 0;
	virtual void attack(Goblin& goblin) = 0;
	virtual void beAttackedBy(Player& p) = 0;
	void beSlain();
	void notify();
};

class Human :public Enemy {
public:
	Human();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
	virtual void beAttackedBy(Player& p) override;
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
	std::shared_ptr<Gold> drgold;
public:
	Dragon();
};

class Halfling :public Enemy {
public:
	Halfling();
};

#endif // !ENEMY_H
