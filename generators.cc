#include "generators.h"
#include "enemy.h"

EnemyGenerator::EnemyGenerator(Floor *floor)
    : floor{floor} {}

EnemyGenerator::~EnemyGenerator() {}

std::shared_ptr<Enemy> EnemyGenerator::generate()
{
    int i = rand() % total;
    if (0 <= i && i < 4) // human.
}
