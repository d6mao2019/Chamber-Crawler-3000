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

int Character::getHP() const { return HP; }
int Character::getAtk() const { return Atk; }
int Character::getDef() const { return Def; }
int Character::getGold() const { return gold; }
int Character::getRow() const { return row; }
int Character::getCol() const { return col; }

void Character::setHP(int new_HP) { HP = new_HP; }
void Character::setGold(int new_gold) { gold = new_gold; }

void Character::move(Direction direction)
{
	switch (direction)
	{
	case Direction::no:
		--row;
	case Direction::so:
		++row;
	case Direction::we:
		--col;
	case Direction::ea:
		++col;
	case Direction::nw:
		--row;
		--col;
	case Direction::ne:
		--row;
		++col;
	case Direction::sw:
		++row;
		--col;
	case Direction::se:
		++row;
		++col;
	}
}

bool adjacent(Character &c1, Character &c2)
{
	int dist_square = pow(c1.getRow() - c2.getRow(), 2) + pow(c1.getCol() - c2.getCol(), 2);
	return dist_square == 1 || dist_square == 2;
}

/* Useless function...
int Character::calcDamageTo(const Character &other) const
{
	double atk = getAtk();
	double def = other.getDef();
	int damage = ceil(100 / (100 + def) * atk);
	return damage;
}
*/
