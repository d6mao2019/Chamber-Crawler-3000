#include "enemy.h"
#include "player.h"

void Enemy::notify() { floor->beNotifiedBy(*this); }

Human::Human()
	: Character{140, 20, 20}
{
}

Dwarf::Dwarf()
	: HP{100}, Atk{20}, Def{30} {}

Elf::Elf()
	: HP{140}, Atk{30}, Def{10} {}

Orcs::Orcs()
	: HP{180}, Atk{30}, Def{25} {}
