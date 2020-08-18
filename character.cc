#include "character.h"
#include <stdexcept>
#include <string>
#include "util.h"

Character::Character(double MaxHP, double HP, double Atk, double Def,
					 int gold, int row, int col, Floor *floor)
	: MaxHP{MaxHP}, HP{HP}, Atk{Atk}, Def{Def},
	  gold{gold}, row{row}, col{col}, floor{floor} {}

double Character::getHP() const { return HP; }
double Character::getAtk() const { return Atk; }
double Character::getDef() const { return Def; }
double Character::getMaxHP() const { return MaxHP; }
int Character::getGold() const { return gold; }
int Character::getRow() const { return row; }
int Character::getCol() const { return col; }

void Character::setHP(double new_hp) { new_hp < 0 ? HP = 0 : (new_hp > MaxHP ? HP = MaxHP : HP = new_hp); }
void Character::setAtk(double new_atk) { new_atk < 0 ? Atk = 0 : Atk = new_atk; }
void Character::setDef(double new_def) { Def < 0 ? Def = 0 : Def = new_def; }
void Character::setGold(int new_gold) { gold = new_gold; }
void Character::setLocation(int new_row, int new_col)
{
	row = new_row;
	col = new_col;
}
void Character::setFloor(Floor *new_floor) { floor = new_floor; }
void Character::move(Direction direction)
{
	std::pair<int, int> new_loc = getNewLoc(row, col, direction);
	std::swap(row, new_loc.first);
	std::swap(col, new_loc.second);
}
