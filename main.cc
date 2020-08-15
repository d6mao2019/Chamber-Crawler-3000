#include "character.h"
#include "player.h"
#include "enemy.h"
#include "gold.h"
#include "potion.h"
#include "floor.h"
#include "output.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
#define cin cin
#include "output.h"

Floor readFloor(ifstream &f, std::vector<std::vector<std::pair<int, int>>> &availables, std::shared_ptr<Player> player)
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
    vector<char> firstRow;
    for (int i = 0; i < line.length(); ++i)
    {

        firstRow.push_back(line[i]);
    }
    text_display.push_back(firstRow);
    int row = 1;
    do
    {
        vector<char> newRow;
        getline(f, line);
        for (int col = 0; col < line.length(); ++col)
        {
            shared_ptr<Potion> newPotion;
            shared_ptr<Gold> newGold;
            std::pair<int, int> newPair;
            switch (line[col])
            {
            case '0':
                newRow.push_back('P');
                newPotion = make_shared<HPBoost>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '1':
                newRow.push_back('P');
                newPotion = make_shared<AtkBoost>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '2':
                newRow.push_back('P');
                newPotion = make_shared<DefBoost>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '3':
                newRow.push_back('P');
                newPotion = make_shared<HPWound>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '4':
                newRow.push_back('P');
                newPotion = make_shared<AtkWound>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '5':
                newRow.push_back('P');
                newPotion = make_shared<DefWound>(row, col);
                potion_list.push_back(newPotion);
                break;
            case '6':
                newRow.push_back('G');
                newGold = make_shared<Normal>(row, col);
                gold_list.push_back(newGold);
                break;
            case '7':
                newRow.push_back('G');
                newGold = make_shared<SmallHoard>(row, col);
                gold_list.push_back(newGold);
                break;
            case '8':
                newRow.push_back('G');
                newGold = make_shared<MerchantHoard>(row, col);
                gold_list.push_back(newGold);
                break;
            case '9':
                newRow.push_back('G');
                newGold = make_shared<DragonHoard>(row, col);
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
            shared_ptr<Enemy> newEnemy;
            switch (text_display[i][j])
            {
            case 'H':
                newEnemy = make_shared<Human>(i, j);
                enemy_list.push_back(newEnemy);
                break;
            case 'W':
                newEnemy = make_shared<Dwarf>(i, j);
                enemy_list.push_back(newEnemy);
                break;
            case 'E':
                newEnemy = make_shared<Elf>(i, j);
                enemy_list.push_back(newEnemy);
                break;
            case 'O':
                newEnemy = make_shared<Orc>(i, j);
                enemy_list.push_back(newEnemy);
                break;
            case 'M':
                newEnemy = make_shared<Merchant>(i, j);
                enemy_list.push_back(newEnemy);
                break;
            case 'D':
                for (int w = 0; w < gold_list.size(); ++w)
                {
                    shared_ptr<Gold> theGold = gold_list[w];
                    if (theGold->getRow() <= i + 1 && theGold->getRow() >= i - 1 && theGold->getCol() <= j + 1 && theGold->getCol() >= j - 1 && theGold->canBepickedup() == 0)
                    {
                        newEnemy = make_shared<Dragon>(i, j, theGold);
                        enemy_list.push_back(newEnemy);
                        break;
                    }
                }
                break;
            case 'L':
                newEnemy = make_shared<Halfling>(i, j);
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
    vector<Floor> floors;
    std::vector<std::vector<char>> mainEmptyMap;
    std::vector<std::vector<std::pair<int, int>>> availables = {prsA, prsB, prsC, prsD, prsE};
    std::shared_ptr<Player> pl;
    ifstream inputMap;
    ifstream ff{"1.in"};
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
            pl = make_shared<Shade>();
            message = "You have selected Shade.";
        }
        else if (cmd == "d")
        {
            pl = make_shared<Drow>();
            message = "You have selected Drow.";
        }
        else if (cmd == "v")
        {
            pl = make_shared<Vampire>();
            message = "You have selected Vampire.";
        }
        else if (cmd == "g")
        {
            pl = make_shared<Goblin>();
            message = "You have selected Goblin.";
        }
        else if (cmd == "t")
        {
            pl = make_shared<Troll>();
            message = "You have selected Troll.";
        }
        else if (cmd == "q")
        {
            return 0;
        }
        else
        {
            message = "Error: unrecgonized race.";
        }
        std::cout << message << std::endl;

        if (argc > 1) // read in map.
        {
            Floor firFloor = readFloor(inputMap, availables, pl);
            Floor secFloor = readFloor(inputMap, availables, pl);
            Floor thiFloor = readFloor(inputMap, availables, pl);
            Floor forFloor = readFloor(inputMap, availables, pl);
            Floor fifFloor = readFloor(inputMap, availables, pl);
            floors = {firFloor, secFloor, thiFloor, forFloor, fifFloor};
        }
        else // read in empty map for random generate later.
        {
            for (auto i : charMap)
            {
                std::vector<char> vc;
                for (auto c : i)
                {
                    if (c!='\n')
                    {
                        vc.push_back(c);

                    }
                }
                mainEmptyMap.push_back(vc);
            }
        }
        Floor curFloor;
        while (floorNum < 5 && !cin.fail())
        {
            if (argc > 1)
                curFloor = floors[floorNum];
            else
                curFloor = Floor{mainEmptyMap, pl, availables, 20, 10, 10};
            std::cout << curFloor;

            while (cin >> cmd)
            {
                try
                {
                    if (cmd == "no")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow() - 1, pl->getCol()))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the north.";
                    }
                    else if (cmd == "so")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow() + 1, pl->getCol()))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the south.";
                    }
                    else if (cmd == "we")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow(), pl->getCol() - 1))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the west.";
                    }
                    else if (cmd == "ea")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow(), pl->getCol() + 1))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the east.";
                    }
                    else if (cmd == "nw")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow() - 1, pl->getCol() - 1))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the north west.";
                    }
                    else if (cmd == "ne")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow() - 1, pl->getCol() + 1))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the north east.";
                    }
                    else if (cmd == "sw")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow() + 1, pl->getCol() - 1))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the south west.";
                    }
                    else if (cmd == "se")
                    {
                        if (curFloor.move_player(pl->getRow(), pl->getCol(), pl->getRow() + 1, pl->getCol() + 1))
                        {
                            floorNum += 1;
                            break;
                        }
                        message = "Player moved to the south east.";
                    }
                    else if (cmd == "u") // use potion.
                    {
                        cin >> direction;
                        curFloor.consume_potion(direction);
                        message = "Player consume potion.";
                        // need to determine whether cosumption is successful.
                    }
                    else if (cmd == "a") // attack enemy.
                    {
                        cin >> direction;
                        curFloor.attack_enemy(direction);
                        message = "Player atk.";
                    }
                    else if (cmd == "f") // stops enemies from moving until this key is pressed again.
                    {
                        curFloor.ERMSwitch();
                    }
                    else if (cmd == "r") // restart game.
                    {
                        floorNum = 0;
                        if (argc > 1)
                        {
                            inputMap.clear();
                            inputMap.seekg(0, inputMap.beg);
                        }
                        // shoule "rerun" main.
                        break;
                    }
                    else if (cmd == "q") // quit game.
                        return 0;
                    else
                        message = "Error: unrecognized command.";
                }
                catch (std::runtime_error &e)
                {
                    message = e.what();
                }

                curFloor.tick();
                if (pl->getHP() <= 0)
                {
                    message = "Player got killed. Do you want to restart(r) or quit(q)?";
                    std::cout << message;
                    while (cin >> cmd && (cmd == "r" || cmd == "q"))
                    {
                        if (cmd == "q")
                            return 0;
                        else if (cmd == "r")
                            break;
                        else // invalid command.
                            std::cout << "Invalid command. Do you want to restart(r) or quit(q)?";
                    }
                }
                std::cout << curFloor;
                std::cout << *pl;
                std::cout << message << std::endl;
            }
            if (cmd == "r")
            {
                break;
            } // while command processing.
        }     // while floors.

        // all floors cleared. choose whether to restart or quit.
        if (cmd != "r")
        {
            while (cin >> cmd && (cmd == "r" || cmd == "q"))
            {
                if (cmd == "r")
                    break;
                else
                    return 0;
            }
        }
    } //while whole game.
} // main
