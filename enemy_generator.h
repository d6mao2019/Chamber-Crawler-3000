#ifndef ENEMYGENERATOR_H
#define ENEMYGENERATOR_H
#include "enemy.h"

class EnemyGenerator
{
private:
    const int human_prob = 4;
    const int dwarf_prob = 3;
    const int halfling_prob = 5;
    const int elf_prob = 2;
    const int orc_prob = 2;
    const int merchant_prob = 2;

public:
    EnemyGenerator(/* args */);
    ~EnemyGenerator();
    Enemy *generate();
};

#endif
