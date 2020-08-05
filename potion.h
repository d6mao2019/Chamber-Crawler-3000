#ifndef POTION_H
#define POTION_H
#include "player.h"
#include <memory>

class Potion : public Player
{
	int effect;
	int row, col;

protected:
	std::unique_ptr<Player> player;

public:
};

class HPBoost : public Potion
{
};

class AtkBoost : public Potion
{
public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

class DefBoost : public Potion
{
public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

class HPWound : public Potion
{
};

class AtkWound : public Potion
{
public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

class DefWound : public Potion
{
public:
	virtual int getHP() const override;
	virtual int getAtk() const override;
	virtual int getDef() const override;
};

#endif // !POTION_H
