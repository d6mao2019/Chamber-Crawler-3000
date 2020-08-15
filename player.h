#ifndef PLAYER_H
#define PLAYER_H
#include "character.h"
class Item;
class Enemy;
class Human;
class Dwarf;
class Elf;
class Orc;
class Merchant;
class Dragon;
class Halfling;
class Floor;

class Player : public Character
{
private:
	double scaling;
	char prev = '.';
	double origAtk;
	double origDef;
	const std::string race;

public:
	// Player constructor.
	Player(double MaxHP, double HP, double Atk, double Def,
		   int gold, int row, int col, double scaling, Floor *floor);
	virtual ~Player();
	bool adjacent(const Enemy &e) const;
	bool adjacent(const Item &i) const;
	double getScal() const;
	char getPrev() const;
	std::string getRace() const;
	void setPrev(char p);
	virtual void attack(Human &human);
	virtual void attack(Dwarf &dwarf);
	virtual void attack(Elf &elf);
	virtual void attack(Orc &orc);
	virtual void attack(Merchant &merchant);
	virtual void attack(Dragon &dragon);
	virtual void attack(Halfling &halfling);
	virtual void beAttackedBy(Enemy &e) = 0;
	void restore();
};
std::ostream &operator<<(std::ostream &out, const Player &pl);

class Shade : public Player
{
	const std::string race = "Shade";

public:
	Shade(int row = 0, int col = 0);
	virtual void beAttackedBy(Enemy &e) override;
	// 0 attack override(s).
};

class Drow : public Player
// all potions have their effect magnified by 1.5.
{
	const std::string race = "Drow";

public:
	Drow(int row = 0, int col = 0);
	virtual void beAttackedBy(Enemy &e) override;
	// 0 attack override(s).
};

class Vampire : public Player
// has no maximum HP.
// gains 5 HP every successful attack except for dwarfs.
// loses 5 HP every successful attack on dwarfs.
{
	const std::string race = "Vampire";

public:
	Vampire(int row = 0, int col = 0);
	virtual void beAttackedBy(Enemy &e) override;
	// 7 attack override(s).
	virtual void attack(Human &human) override;
	virtual void attack(Dwarf &dwarf) override;
	virtual void attack(Elf &elf) override;
	virtual void attack(Orc &orc) override;
	virtual void attack(Merchant &merchant) override;
	virtual void attack(Dragon &dragon) override;
	virtual void attack(Halfling &halfling) override;
};

class Troll : public Player
// regains 5 HP every turn (capped at 120).
{
	const std::string race = "Troll";

public:
	Troll(int row = 0, int col = 0);
	virtual void beAttackedBy(Enemy &e) override;
	// 0 attack override(s).
};

class Goblin : public Player
// steals 5 gold from every slain enemy.
{
	const std::string race = "Goblin";

public:
	Goblin(int row = 0, int col = 0);
	virtual void beAttackedBy(Enemy &e) override;
	// 7 attack override(s).
	virtual void attack(Human &human) override;
	virtual void attack(Dwarf &dwarf) override;
	virtual void attack(Elf &elf) override;
	virtual void attack(Orc &orc) override;
	virtual void attack(Merchant &merchant) override;
	virtual void attack(Dragon &dragon) override;
	virtual void attack(Halfling &halfling) override;
};

#endif // !PLAYER_H
