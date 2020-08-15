#include "character.h"
#include <stdexcept>
#include <string>
#include <math.h>

std::istream &operator>>(std::istream &in, Direction direction)
{
	std::string s;
	in >> s;
	if (s == "no")
		direction = Direction::no;
	else if (s == "so")
		direction = Direction::so;
	else if (s == "we")
		direction = Direction::we;
	else if (s == "ea")
		direction = Direction::ea;
	else if (s == "nw")
		direction = Direction::nw;
	else if (s == "ne")
		direction = Direction::ne;
	else if (s == "sw")
		direction = Direction::sw;
	else if (s == "se")
		direction = Direction::se;
	else
		throw std::runtime_error{"Error: invalid direction."};
	return in;
}

Character::Character(double MaxHP, double HP, double Atk, double Def, int gold, int row, int col)
	: MaxHP{MaxHP}, HP{HP}, Atk{Atk}, Def{Def}, gold{gold}, row{row}, col{col} {}

double Character::getHP() const { return HP; }
double Character::getAtk() const { return Atk; }
double Character::getDef() const { return Def; }
double Character::getMaxHP() const { return MaxHP; }
int Character::getGold() const { return gold; }
int Character::getRow() const { return row; }
int Character::getCol() const { return col; }

void Character::setHP(double new_HP) { new_HP < 0 ? HP = 0 : (new_HP > MaxHP ? HP = MaxHP : HP = new_HP); }
void Character::setAtk(double new_atk) { new_atk < 0 ? Atk = 0 : Atk = new_atk; }
void Character::setDef(double new_def) { Def < 0 ? Def = 0 : Def = new_def; }
void Character::setGold(int new_gold) { gold = new_gold; }

void Character::setLocation(int new_row, int new_col)
{
	row = new_row;
	col = new_col;
}

void Character::move(Direction direction)
{
	switch (direction)
	{
	case Direction::no:
		--row;
		break;
	case Direction::so:
		++row;
		break;
	case Direction::we:
		--col;
		break;
	case Direction::ea:
		++col;
		break;
	case Direction::nw:
		--row;
		--col;
		break;
	case Direction::ne:
		--row;
		++col;
		break;
	case Direction::sw:
		++row;
		--col;
		break;
	case Direction::se:
		++row;
		++col;
		break;
	}
}
