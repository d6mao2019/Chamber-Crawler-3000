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
#define cin std::cin
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

int main(int argc, char *argv[])
{
    int floorNum = 0;
    std::string cmd;
    Direction direction = Direction::no;
    std::string message;
    std::vector<Floor> floors;
    std::vector<std::vector<std::pair<int, int>>> availables = {prsA, prsB, prsC, prsD, prsE};
    std::shared_ptr<Player> pl;
    std::ifstream inputMap;
    std::ifstream ff{"1.in"};
    if (argc > 1)
    {
        inputMap.open(argv[1]);
    }

    while (!cin.fail())
    {
        message = "Please select your race.";
        std::cout << message << std::endl;
        cin >> cmd;
        if (cmd == "s")
        {
            pl = std::make_shared<Shade>();
            message = "You have selected Shade.";
        }
        else if (cmd == "d")
        {
            pl = std::make_shared<Drow>();
            message = "You have selected Drow.";
        }
        else if (cmd == "v")
        {
            pl = std::make_shared<Vampire>();
            message = "You have selected Vampire.";
        }
        else if (cmd == "g")
        {
            pl = std::make_shared<Goblin>();
            message = "You have selected Goblin.";
        }
        else if (cmd == "t")
        {
            pl = std::make_shared<Troll>();
            message = "You have selected Troll.";
        }
        else if (cmd == "q")
        {
            return 0;
        }
        else
        {
            message = "Error: Unrecgonized race.";
        }
        std::cout << message << std::endl;
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
        Floor curFloor;
        bool tempERM = 1;
        while (floorNum < 5 && !cin.fail())
        {
            if (argc > 1)
            {
                curFloor = readFloor(inputMap, availables, pl);
            }
            else
            {
                curFloor = Floor{mainEmptyMap, pl, availables, 20, 10, 10};
            }
            std::cout << curFloor;
            std::cout << "Race: " << pl->getRace() << " Gold: " << pl->getGold() << std::setw(64 - pl->getRace().size() - std::to_string(pl->getGold()).size()) << "Floor : " << floorNum + 1 << std::endl;
            std::cout << *pl;
            if (floorNum == 0)
            {
                std::cout << "Action: Player character has spawned." << std::endl;
            }
            else
            {
                std::cout << "Action: Player is on new floor" << std::endl;
            }
            if (curFloor.getERM() != tempERM)
            {
                curFloor.ERMSwitch();
            }
            while (cin >> cmd)
            {
                try
                {
                    std::stringstream ss{cmd};
                    if (ss >> direction) // move player.
                    {
                        if (curFloor.move_player(direction))
                        {
                            floorNum += 1;
                            if (floorNum < 4)
                            {
                                std::cout << "Next Floor!" << std::endl;
                                tempERM = curFloor.getERM();
                            }
                            break;
                        }
                        std::cout << "Action: Player moved to the " << direction << "." << std::endl;
                    }
                    else if (cmd == "u") // consume potion.
                    {
                        cin >> direction;
                        curFloor.consume_potion(direction);
                        std::cout << "Action: Player consumed potion." << std::endl;
                    }
                    else if (cmd == "a") // attack enemy.
                    {
                        cin >> direction;
                        curFloor.attack_enemy(direction);
                        std::cout << "Action: Player attacked an enemy." << std::endl;
                    }
                    else if (cmd == "f") // stops enemies from moving until this key is pressed again.
                    {
                        curFloor.ERMSwitch();
                        if (curFloor.getERM() == 0)
                            std::cout << "Enemy random move disabled." << std::endl;
                        else
                            std::cout << "Enemy random move enabled." << std::endl;
                    }
                    else if (cmd == "r") // restart game.
                    {
                        floorNum = 0;
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
                        std::cout << "Quiting game." << std::endl;
                        return 0;
                    }
                    else
                        std::cout << "Error: Unrecognized command." << std::endl;
                }
                catch (std::runtime_error &e)
                {
                    message = e.what();
                }
                if (cmd == "no" || cmd == "so" || cmd == "ea" || cmd == "we" || cmd == "ne" || cmd == "nw" || cmd == "se" || cmd == "sw" || cmd == "a" || cmd == "u")
                {
                    curFloor.tick();
                    if (pl->getHP() <= 0)
                    {
                        std::cout << "Player got killed. Do you want to restart(r) or quit(q)?" << std::endl;
                        while (cin >> cmd)
                        {
                            if (cmd == "q")
                            {
                                std::cout << "Quiting gmae." << std::endl;
                                return 0;
                            }
                            else if (cmd == "r")
                            {
                                std::cout << "Game restarts!" << std::endl;
                                floorNum = 0;
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
                    std::cout << curFloor;
                    std::cout << "Race: " << pl->getRace() << " Gold: " << pl->getGold() << std::setw(60 - pl->getRace().size() - std::to_string(pl->getGold()).size()) << "Floor : " << floorNum + 1 << std::endl;
                    std::cout << *pl;
                    std::cout << message << std::endl;
                }
                if (cmd == "r")
                    break;
            } //while (cin >> cmd)
            if (cmd == "r")
                break;
        } // while (floorNum < 5 && !cin.fail())

        // all floors cleared. choose whether to restart or quit.
        if (cmd != "r" && floorNum == 5)
        {
            std::cout << "You made it through the Dungeon!" << std::endl;
            std::cout << "The treasures are all yours! " << std::endl;
            std::cout << "Do you want to try another dungeon(r) or quit(q)?" << std::endl;
            while (cin >> cmd)
            {
                if (cmd == "q")
                    return 0;
                else if (cmd == "r")
                {
                    std::cout << "Game restarts!" << std::endl;
                    floorNum = 0;
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
