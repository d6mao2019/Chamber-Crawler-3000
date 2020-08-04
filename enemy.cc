#include "enemy.h"
#include "player.h"

void Enemy::attack(Shade& shade) {
	int damage = calcDamageTo(shade);
}

void Enemy::beAttackedBy(Player& p) { p.attack(*this); }

Human::Human() 
	:HP{ 140 }, Atk{ 20 }, Def{ 20 } {}
