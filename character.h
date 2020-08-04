#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
protected:
	// invariant: all three artributes cannot drop below zero.

	// current health point.
	int HP;
	// base attack.
	int Atk;
	// base defense.
	int Def;
public:
	virtual int getHP() const;
	virtual int getAtk() const;
	virtual int getDef() const;
};

#endif // !CHARACTER_H
