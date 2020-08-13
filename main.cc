#include "character.h"
#include "player.h"
#include "enemy.h"
#include "gold.h"
#include "potion.h"
#include "floor.h"
#include <iostream>
#include <string>

int main()
{
    char cmd;
    Direction direction;
    Floor floor;
    while (std::cin >> cmd)
    {
        switch (cmd)
        {
        case 'u': // use potion.
            try
            {
                std::cin >> direction;
                /*
                more code goes here.
                */
            }
            catch (std::runtime_error &e)
            {
                std::cerr << e.what() << std::endl;
            }
        case 'a': // attack enemy.
            try
            {
                std::cin >> direction;
                /*
                more code goes here.
                */
            }
            catch (std::runtime_error &e)
            {
                std::cerr << e.what() << std::endl;
            }
        case 's': //
        case 'd':
        case 'v':
        case 'g':
        case 't':
        case 'f': // stops enemies from moving until this key is pressed again.
        case 'r': // restart game.
        case 'q': // exit game.
        default:
            std::cerr << "Error: unrecognized command." << std::endl;
        } // switch
    }     // while
} // main
