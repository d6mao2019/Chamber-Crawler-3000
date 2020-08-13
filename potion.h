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
};

class DefBoost : public Potion
{
public:
};

class HPWound : public Potion
{
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
