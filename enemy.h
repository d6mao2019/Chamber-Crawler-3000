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
	virtual void beAttackedBy(Player& p);
};

class Human :public Enemy {
public:
	Human();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
};

class Dwarf :public Enemy {
public:
	Dwarf();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
};

class Elf :public Enemy {
public:
	Elf();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
};

class Orcs :public Enemy {
public:
	Orcs();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
};

class Merchant :public Enemy {
	static bool neutral;
public:
	Merchant();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
};

class Dragon :public Enemy {
public:
	Dragon();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
};

class Halfling :public Enemy {
public:
	Halfling();
	virtual void attack(Shade& shade) override;
	virtual void attack(Drow& drow) override;
	virtual void attack(Vampire& vampire) override;
	virtual void attack(Troll& troll) override;
	virtual void attack(Goblin& goblin) override;
};

#endif // !ENEMY_H
