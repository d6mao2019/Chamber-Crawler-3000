#include "player.h"
#include "enemy.h"

void Player::beAttackedBy(Enemy& e) { e.attack(*this); }
