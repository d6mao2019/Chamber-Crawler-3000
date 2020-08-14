#ifndef POTION_H
#define POTION_H
#include "player.h"
#include "item.h"
#include <memory>

class Potion : public Item
{
public:
	Potion(int row = 0, int col = 0);
	virtual void consume(Player &pl) = 0;
};

class AtkBoost : public Potion
{
	const int boost = 5;

public:
	AtkBoost(int row = 0, int col = 0);
	virtual void consume(Player &pl) override;
};

class DefBoost : public Potion
{
	const int boost = 5;

public:
	DefBoost(int row = 0, int col = 0);
	virtual void consume(Player &pl) override;
};

class AtkWound : public Potion
{
public:
	const int wound = 5;
	AtkWound(int row = 0, int col = 0);
	virtual void consume(Player &pl) override;
};

class DefWound : public Potion
{
	const int wound = 5;

public:
	DefWound(int row = 0, int col = 0);
	virtual void consume(Player &pl) override;
};

class HPBoost : public Potion
{
	const int hp = 5;

public:
	HPBoost(int row = 0, int col = 0);
	virtual void consume(Player &pl) override;
};

class HPWound : public Potion
{
	const int hp = 5;

public:
	HPWound(int row = 0, int col = 0);
	virtual void consume(Player &pl) override;
};

#endif // !POTION_H
