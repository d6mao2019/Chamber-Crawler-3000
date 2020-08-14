#include "character.h"
#include "player.h"
#include "enemy.h"
#include "gold.h"
#include "potion.h"
#include "floor.h"
#include <iostream>
#include <string>

int main(int argc, char * argv[])
{
    char cmd;
    std::string cmd;
    Direction direction;
    for (int i = 0; i < 5; ++i)
    {
        Floor floor{20, 10, 10};
        while (std::cin >> cmd)
        {
            if (cmd == "u") // use potion.
            {
                try
                {
                    std::cin >> direction;
                    floor.consume_potion(direction);
                }
                catch (std::runtime_error &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
            else if (cmd == "a") // attack enemy.
            {
                try
                {
                    std::cin >> direction;
                    floor.attack_enemy(direction);
                }
                catch (std::runtime_error &e)
                {
                    std::cerr << e.what() << std::endl;
                }
            }
            else if (cmd == "s")
            {
            }
            else if (cmd == "d")
            {
            }
            else if (cmd == "v")
            {
            }
            else if (cmd == "g")
            {
            }
            else if (cmd == "t")
            {
            }
            else if (cmd == "f") // stops enemies from moving until this key is pressed again.
                floor.ERMSwitch();
            else if (cmd == "r") // restart game.
            {
            }
            else if (cmd == "q") // quit game.
            {
            }
            else
                std::cerr << "Error: unrecognized command." << std::endl;
        } // while
    }     // for
} // main
