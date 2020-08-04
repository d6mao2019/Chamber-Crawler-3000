#include "enemy.h"
#include "player.h"

void Enemy::beAttackedBy(Player& p) { p.attack(*this); }
