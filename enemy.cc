#include "enemy.h"
#include "player.h"

void Enemy::attack(Shade& shade) {
	int damage = calcDamageTo(shade);
	int new_HP = shade.getHP() - damage;
	if (new_HP > 0) shade.setHP(new_HP);
	else {
		beSlain(shade);
	}
}

void Enemy::beAttackedBy(Player& p) { p.attack(*this); }

void Enemy::beSlain(Player& p) {
	p.
}

Human::Human()
	: HP{ 140 }, Atk{ 20 }, Def{ 20 } {}

Dwarf::Dwarf()
	: HP{ 100 }, Atk{ 20 }, Def{ 30 } {}

Elf::Elf()
	: HP{ 140 }, Atk{ 30 }, Def{ 10 } {}

Orcs::Orcs()
	: HP{ 180 }, Atk{ 30 }, Def{ 25 } {}
