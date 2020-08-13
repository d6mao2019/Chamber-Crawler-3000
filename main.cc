#include "character.h"
#include "player.h"
#include "enemy.h"
#include "gold.h"
#include "potion.h"
#include "floor.h"
#include <iostream>

int main()
{
    char cmd;
    while (std::cin >> cmd)
    {
        switch (cmd)
        {
        case 'u': // use potion.
        case 'a': // attack enemy.
        case 's': //
        case 'd':
        case 'v':
        case 'g':
        case 't':
        case 'f': // stops enemies from moving until this key is pressed again.
        case 'r': // restart game.
        case 'q': // exit game.
        }
    }
}
