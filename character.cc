#include "character.h"

Character::Character(int HP, int Atk, int Def, int gold, int row, int col)
	: HP{HP}, Atk{Atk}, Def{Def}, gold{gold}, row{row}, col{col} {}

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

/* Useless function...
int Character::calcDamageTo(const Character &other) const
{
	double atk = getAtk();
	double def = other.getDef();
	int damage = ceil(100 / (100 + def) * atk);
	return damage;
}
*/
