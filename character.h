#ifndef CHARACTER_H
#define CHARACTER_H

class Character {
	// invariants: HP cannot drop below zero.
	//             Atk and Def should be non-negative integers and should not be modified.

	// current health point.
	int HP;
	// base attack.
	int Atk;
	// base defense.
	int Def;
protected:
	void setHP(int new_HP);
public:
	virtual int getHP() const;
	virtual int getAtk() const;
	virtual int getDef() const;
	// calculates the damage caused by this to other.
	int calcDamageTo(const Character& other);
};


#endif // !CHARACTER_H
