#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "gold.h"
#include "floor.h"
#include "util.h"
#include "output.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
// using namespace std;
//#define cin cin
#include "output.h"

Floor readFloor(std::ifstream &f, std::vector<std::vector<std::pair<int, int>>> &availables, std::shared_ptr<Player> player)
{
    std::vector<std::vector<char>> text_display;
    std::vector<std::shared_ptr<Enemy>> enemy_list;
    std::vector<std::shared_ptr<Potion>> potion_list;
    std::vector<std::shared_ptr<Gold>> gold_list;
    std::vector<std::vector<std::pair<int, int>>> newAvailables;
    for (int i = 0; i < 5; ++i)
    {
        std::vector<std::pair<int, int>> newprs;
        newAvailables.push_back(newprs);
    }
    std::string line;
    getline(f, line);
    std::vector<char> firstRow;
    for (int i = 0; i < line.length(); ++i)
    {

        firstRow.push_back(line[i]);
    }
    text_display.push_back(firstRow);
    int row = 1;
    do
    {
        std::vector<char> newRow;
        getline(f, line);
        for (int col = 0; col < line.length(); ++col)
        {
            std::shared_ptr<Potion> newPotion;
            std::shared_ptr<Gold> newGold;
            std::pair<int, int> newPair;
            switch (line[col])
            {
            case '0':
                newRow.push_back('P');
                newPotion = std::make_shared<HPBoost>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '1':
                newRow.push_back('P');
                newPotion = std::make_shared<AtkBoost>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '2':
                newRow.push_back('P');
                newPotion = std::make_shared<DefBoost>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '3':
                newRow.push_back('P');
                newPotion = std::make_shared<HPWound>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '4':
                newRow.push_back('P');
                newPotion = std::make_shared<AtkWound>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '5':
                newRow.push_back('P');
                newPotion = std::make_shared<DefWound>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '6':
                newRow.push_back('G');
                newGold = std::make_shared<Normal>(row, col);
                gold_list.push_back(newGold);
                break;
            case '7':
                newRow.push_back('G');
                newGold = std::make_shared<SmallHoard>(row, col);
                gold_list.push_back(newGold);
                break;
            case '8':
                newRow.push_back('G');
                newGold = std::make_shared<MerchantHoard>(row, col);
                gold_list.push_back(newGold);
                break;
            case '9':
                newRow.push_back('G');
                newGold = std::make_shared<DragonHoard>(row, col);
                gold_list.push_back(newGold);
                break;
            case '.':
                newRow.push_back('.');
                for (int i = 0; i != availables.size(); ++i)
                {
                    for (int j = 0; j < availables[i].size(); ++j)
                    {
                        if (availables[i][j].first == row && availables[i][j].second == col)
                        {
                            newPair = {row, col};
                            newAvailables[i].push_back(newPair);
                        }
                    }
                }
                break;
            case '@':
                newRow.push_back('@');
                player->setLocation(row, col);
                break;
            default:
                newRow.push_back(line[col]);
            } // switch
        }
        text_display.push_back(newRow); // do
        row += 1;

    } while (!(line[0] == '|' && line[1] == '-'));

    for (int i = 0; i < text_display.size(); ++i)
    {
        for (int j = 0; j < text_display[i].size(); ++j)
        {
            std::shared_ptr<Enemy> newEnemy;
            switch (text_display[i][j])
            {
            case 'H':
                newEnemy = std::make_shared<Human>(i, j, nullptr);
                enemy_list.push_back(newEnemy);
                break;
            case 'W':
                newEnemy = std::make_shared<Dwarf>(i, j, nullptr);
                enemy_list.push_back(newEnemy);
                break;
            case 'E':
                newEnemy = std::make_shared<Elf>(i, j, nullptr);
                enemy_list.push_back(newEnemy);
                break;
            case 'O':
                newEnemy = std::make_shared<Orc>(i, j, nullptr);
                enemy_list.push_back(newEnemy);
                break;
            case 'M':
                newEnemy = std::make_shared<Merchant>(i, j, nullptr);
                enemy_list.push_back(newEnemy);
                break;
            case 'D':
                for (int w = 0; w < gold_list.size(); ++w)
                {
                    std::shared_ptr<Gold> theGold = gold_list[w];
                    if (theGold->getRow() <= i + 1 && theGold->getRow() >= i - 1 && theGold->getCol() <= j + 1 && theGold->getCol() >= j - 1 && theGold->canBepickedup() == 0)
                    {
                        std::shared_ptr<DragonHoard> theGoldDr = std::dynamic_pointer_cast<DragonHoard>(gold_list[w]);
                        newEnemy = std::make_shared<Dragon>(i, j, theGoldDr, nullptr);
                        enemy_list.push_back(newEnemy);
                        break;
                    }
                }
                break;
            case 'L':
                newEnemy = std::make_shared<Halfling>(i, j, nullptr);
                enemy_list.push_back(newEnemy);
                break;
            }
        }
    }
    Floor newFloor = Floor(text_display, enemy_list, potion_list, gold_list, player, newAvailables);
    return newFloor;
}

bool quit_game()
{
    char cmd;
    std::cout << "Quit game? (y/n)" << std::endl;
    while (std::cin >> cmd)
    {
        if (cmd == 'y')
        {
            return true;
        }
        else if (cmd == 'n')
            return false;
        else
            std::cout << "Error: Unrecgonized command. Please enter 'y' if you do want to quit and 'n' to resume." << std::endl;
    }
    return true;
}

bool select_race(std::string &cmd, std::shared_ptr<Player> &player)
{
    std::cout << "Please select your race." << std::endl;
    while (std::cin >> cmd)
    {
        if (cmd == "s")
        {
            player = std::make_shared<Shade>();
            std::cout << "You have selected " << player->getRace() << "." << std::endl;
            return false;
        }
        else if (cmd == "d")
        {
            player = std::make_shared<Drow>();
            std::cout << "You have selected " << player->getRace() << "." << std::endl;
            return false;
        }
        else if (cmd == "v")
        {
            player = std::make_shared<Vampire>();
            std::cout << "You have selected " << player->getRace() << "." << std::endl;
            return false;
        }
        else if (cmd == "g")
        {
            player = std::make_shared<Goblin>();
            std::cout << "You have selected " << player->getRace() << "." << std::endl;
            return false;
        }
        else if (cmd == "t")
        {
            player = std::make_shared<Troll>();
            std::cout << "You have selected " << player->getRace() << "." << std::endl;
            return false;
        }
        else if (cmd == "q")
        {
            bool quit = quit_game();
            if (quit)
                return true;
            else
                std::cout << "Please select your race." << std::endl;
        }
        else
            std::cout << "Error: Unrecognized race. Please input command again." << std::endl;
    }
    return true; // program should terminate.
}

void print(const Floor &floor, const Player &player, int floor_num)
{
    std::cout << floor;
    std::cout << "Race: " << player.getRace() << " Gold: " << player.getGold()
              << std::setw(64 - player.getRace().size() - std::to_string(player.getGold()).size())
              << "Floor : " << floor_num + 1 << std::endl;
    std::cout << player;
}

std::string compare_attributes(std::vector<double> old_attributes, std::vector<double> new_attributes)
{
    std::string result;
    if (old_attributes[0] != new_attributes[0])
    {
        if (new_attributes[0] - old_attributes[0] > 0)
            result += "HP +" + std::to_string(abs(new_attributes[0] - old_attributes[0]));
        else
            result += "HP -" + std::to_string(abs(new_attributes[0] - old_attributes[0]));
    }
    if (old_attributes[1] != new_attributes[1])
    {
        if (new_attributes[1] - old_attributes[1] > 0)
            result += "Atk +" + std::to_string(abs(new_attributes[1] - old_attributes[1]));
        else
            result += "Atk -" + std::to_string(abs(new_attributes[1] - old_attributes[1]));
    }
    if (old_attributes[2] != new_attributes[2])
    {
        if (new_attributes[2] - old_attributes[2] > 0)
            result += "Def +" + std::to_string(abs(new_attributes[2] - old_attributes[2]));
        else
            result += "Def -" + std::to_string(abs(new_attributes[2] - old_attributes[2]));
    }
    return result;
}

int main(int argc, char *argv[])
{
    int floor_index = 0;
    std::string cmd;
    Direction direction = Direction::no;
    std::string message;
    // std::vector<Floor> all_floors;
    std::vector<std::vector<std::pair<int, int>>> availables = {prsA, prsB, prsC, prsD, prsE};
    std::shared_ptr<Player> player;
    std::ifstream inputMap;
    std::ifstream ff{"1.in"};
    if (argc > 1)
    {
        inputMap.open(argv[1]);
    }

    while (!std::cin.fail())
    {
        bool quit = select_race(cmd, player);
        if (quit)
            return 0;

        std::vector<std::vector<char>> mainEmptyMap;
        for (auto i : charMap)
        {
            std::vector<char> vc;
            for (auto c : i)
            {
                if (c != '\n')
                {
                    vc.push_back(c);
                }
            }
            mainEmptyMap.push_back(vc);
        }
        Floor floor;
        bool ERM = 1;

        while (floor_index < 5 && !std::cin.fail())
        {
            if (argc > 1)
                floor = readFloor(inputMap, availables, player);
            else
                floor = Floor{mainEmptyMap, player, availables, 20, 10, 10};
            print(floor, *player, floor_index);

            if (floor_index == 0)
                std::cout << "Player character spawned. Starting on the first floor." << std::endl;
            else
                std::cout << "Player got to the next floor." << std::endl;
            if (floor.getERM() != ERM)
                floor.ERMSwitch();

            while (std::cin >> cmd)
            {
                try
                {
                    if (is_direction(cmd)) // move player.
                    {
                        std::stringstream ss{cmd};
                        ss >> direction;
                        bool next_floor = floor.move_player(direction);
                        if (next_floor)
                        {
                            ++floor_index;
                            if (floor_index < 4)
                            {
                                std::cout << "Next Floor!" << std::endl;
                                ERM = floor.getERM();
                            }
                            break;
                        }
                        message = "Action: Player moved to the " + getName(direction) + ".";
                    }
                    else if (cmd == "u") // consume potion.
                    {
                        std::vector<double> old_attributes{player->getHP(), player->getAtk(), player->getDef()};
                        std::cin >> direction;
                        floor.consume_potion(direction);
                        std::vector<double> new_attributes{player->getHP(), player->getAtk(), player->getDef()};
                        message = "Action: Player consumed a potion. " + compare_attributes(old_attributes, new_attributes) + ".";
                    }
                    else if (cmd == "a") // attack enemy.
                    {
                        std::cin >> direction;
                        floor.attack_enemy(direction);
                        message = "Action: Player attacked an enemy.";
                    }
                    else if (cmd == "f") // stops enemies from moving until this key is pressed again.
                    {
                        floor.ERMSwitch();
                        if (floor.getERM() == 0)
                            std::cout << "Enemy random move disabled." << std::endl;
                        else
                            std::cout << "Enemy random move enabled." << std::endl;
                    }
                    else if (cmd == "r") // restart game.
                    {
                        floor_index = 0;
                        if (argc > 1)
                        {
                            inputMap.clear();
                            inputMap.seekg(0, inputMap.beg);
                        }
                        std::cout << "Game restarts!" << std::endl;
                        break;
                    }
                    else if (cmd == "q") // quit game.
                    {
                        bool quit = quit_game();
                        if (quit)
                            return 0;
                        else
                            std::cout << "Enter command." << std::endl;
                    }
                    else
                        message = "Error: Unrecognized command.";
                }
                catch (std::runtime_error &e)
                {
                    message = e.what();
                }
                if (cmd == "no" || cmd == "so" || cmd == "we" || cmd == "ea" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw" || cmd == "a" || cmd == "u")
                {
                    floor.tick();
                    if (player->getHP() <= 0)
                    {
                        std::cout << "Player got killed. Do you want to restart(r) or quit(q)?" << std::endl;
                        while (std::cin >> cmd)
                        {
                            if (cmd == "q")
                            {
                                bool quit = quit_game();
                                if (quit)
                                    return 0;
                                else
                                    std::cout << "Enter command." << std::endl;
                            }
                            else if (cmd == "r")
                            {
                                std::cout << "Game restarts!" << std::endl;
                                floor_index = 0;
                                if (argc > 1)
                                {
                                    inputMap.clear();
                                    inputMap.seekg(0, inputMap.beg);
                                }
                                break;
                            }
                            else // invalid command.
                                std::cout << "Invalid command. Do you want to restart(r) or quit(q)?" << std::endl;
                        }
                    }
                    std::cout << floor;
                    std::cout << "Race: " << player->getRace() << " Gold: " << player->getGold() << std::setw(60 - player->getRace().size() - std::to_string(player->getGold()).size()) << "Floor : " << floor_index + 1 << std::endl;
                    std::cout << *player;
                    std::cout << message << std::endl;
                }
                if (cmd == "r")
                    break;
            }
            if (cmd == "r")
                break;
        }

        // all floors cleared. choose whether to restart or quit.
        if (cmd != "r" && floor_index == 5)
        {
            std::cout << "You made it through the Dungeon!" << std::endl;
            std::cout << "The treasures are all yours! " << std::endl;
            std::cout << "Do you want to try another dungeon(r) or quit(q)?" << std::endl;
            while (std::cin >> cmd)
            {
                if (cmd == "q")
                {
                    bool quit = quit_game();
                    if (quit)
                        return 0;
                    else
                        std::cout << "Enter command." << std::endl;
                }
                else if (cmd == "r")
                {
                    std::cout << "Game restarts!" << std::endl;
                    floor_index = 0;
                    if (argc > 1)
                    {
                        inputMap.clear();
                        inputMap.seekg(0, inputMap.beg);
                    }
                    break;
                }
                else // invalid command.
                    std::cout << "Invalid command. Do you want to restart(r) or quit(q)?" << std::endl;
            }
        }
    } //while whole game.
} // main
