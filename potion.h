#ifndef POTION_H
#define POTION_H
#include "player.h"
#include <memory>

class Potion : public Player
{
	const int effect;
	int row, col;

protected:
	std::shared_ptr<Player> player;

public:
	virtual void modifyPlayer() = 0;
};

class HPBoost : public Potion
{
public:
	virtual void modifyPlayer() override;
};

class AtkBoost : public Potion
{
public:
	virtual void modifyPlayer() override;
};

class DefBoost : public Potion
{
public:
	virtual void modifyPlayer() override;
};

class HPWound : public Potion
{
public:
	virtual void modifyPlayer() override;
};

class AtkWound : public Potion
{
public:
	virtual void modifyPlayer() override;
};

class DefWound : public Potion
{
public:
	virtual void modifyPlayer() override;
};

#endif // !POTION_H
