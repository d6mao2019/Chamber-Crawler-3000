#ifndef POTION_H
#define POTION_H
#include "player.h"
#include <memory>

class Potion : public Player
{
	const double effect;
	const double scaling;

protected:
	std::shared_ptr<Player> player;

public:
	Potion(int effect, int scaling, int row, int col);
	virtual double getHP() const override;
	virtual double getAtk() const override;
	virtual double getDef() const override;
};

class AtkBoost : public Potion
{
public:
	AtkBoost(int row, int col, std::shared_ptr<Player> p);
};

class DefBoost : public Potion
{
public:
};

class AtkWound : public Potion
{
public:
};

class DefWound : public Potion
{
public:
};

#endif // !POTION_H
