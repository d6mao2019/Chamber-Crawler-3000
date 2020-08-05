#ifndef POTION_H
#define POTION_H
#include "player.h"
#include <memory>

class Potion : public Player
{
protected:
	std::unique_ptr<Player> player;

public:
};

class HPBoost : public Potion
{
	const int HP_boost = 5;
};

class AtkBoost : public Potion
{
	const int atk_boost = 5;

public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

class DefBoost : public Potion
{
	const int def_boost = 5;

public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

class HPWound : public Potion
{
	const int HP_wound = 5;
};

class AtkWound : public Potion
{
	const int atd_wound = 5;

public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

class DefWound : public Potion
{
	const int def_wound = 5;

public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

#endif // !POTION_H
