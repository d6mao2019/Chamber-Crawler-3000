#ifndef ENEMYGENERATOR_H
#define ENEMYGENERATOR_H
#include <memory>
class Enemy;

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
    EnemyGenerator();
    ~EnemyGenerator();
    std::shared_ptr<Enemy> generate();
};

#endif // !ENEMYGENERATOR_H
