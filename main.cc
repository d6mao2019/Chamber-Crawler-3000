#include "character.h"
#include "player.h"
#include "enemy.h"
#include "gold.h"
#include "potion.h"
#include "floor.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

Floor readFloor(ifstream &f){
    std::vector<std::vector<char>> text_display;
    std::shared_ptr<Player> player;
    std::vector<std::shared_ptr<Enemy>> enemy_list;
    std::vector<std::shared_ptr<Potion>> potion_list;
    std::vector<std::shared_ptr<Gold>> gold_list;
    std::vector<std::vector<std::pair<int, int>>> availables;
    std::string line;
    getline(f,line);
    for(int i = 0; i < line.length();++i){
        text_display[0].push_back(line[i]);
    }
    int row = 1;
    do{
        getline(f,line);
        for(int col = 0; col < line.length();++col){
            switch(line[col]){
                case '0':
                    text_display[row].push_back('P');
                case '1':
                    text_display[row].push_back('P');
                case '2':
                    text_display[row].push_back('P');
                case '3':
                    text_display[row].push_back('P');
                case '4':
                    text_display[row].push_back('P');
                case '5':
                    text_display[row].push_back('P');
                case '6':
                    text_display[row].push_back('G');
                case '7':
                    text_display[row].push_back('G');
                case '8':
                    text_display[row].push_back('G');
                case '9':
                    text_display[row].push_back('G'); 
                default:    
                    text_display[row].push_back(line[col]);
            }
            
        }
    }

}




int main(int argc, char * argv[])
{
    ifstream inputMap (argv[0]);
    if(argc>0){
        
    }
    char cmd;
    std::string cmd;
    Direction direction;
    std::string message;
    message = "Please select your race.";
    if (cmd == "s")
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
