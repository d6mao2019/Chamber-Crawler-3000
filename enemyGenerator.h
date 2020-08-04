#ifndef eneGener
#define eneGener
#include "enemy.h"

class enemeGenerator
{
private:
    int probHuman, probDwarf, probElf, probOrcs, probMerchant;
public:
    enemeGenerator(/* args */);
    ~enemeGenerator();
    Enemy* generate();
};

enemeGenerator::enemeGenerator(/* args */)
{
}

enemeGenerator::~enemeGenerator()
{
}

#endif
