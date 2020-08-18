#ifndef POTION_H
#define POTION_H
#include "item.h"
#include <memory>
class Player;

class Potion : public Item
{
private:
	const double effect;

public:
	Potion(double effect, int row = 0, int col = 0);
	virtual ~Potion();
	double getEffect() const;
};

class AtkBoost : public Potion
{
public:
	AtkBoost(int row = 0, int col = 0);
};

class DefBoost : public Potion
{
public:
	DefBoost(int row = 0, int col = 0);
};

class AtkWound : public Potion
{
public:
	AtkWound(int row = 0, int col = 0);
};

class DefWound : public Potion
{
public:
	DefWound(int row = 0, int col = 0);
};

class HPBoost : public Potion
{
public:
	HPBoost(int row = 0, int col = 0);
};

class HPWound : public Potion
{
public:
	HPWound(int row = 0, int col = 0);
};

#endif // !POTION_H
