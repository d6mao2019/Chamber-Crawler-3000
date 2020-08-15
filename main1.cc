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
    std::vector<std::vector<std::pair<int, int>>> availables = {prsA, prsB, prsC, prsD, prsE};
    std::shared_ptr<Player> pl;
    ifstream inputMap;
    if (argc > 1)
    {
        inputMap.open(argv[1]);
    }
    pl = make_shared<Shade>();
    Floor firFloor = readFloor(inputMap, availables, pl);
    Floor secFloor = readFloor(inputMap, availables, pl);
    Floor thiFloor = readFloor(inputMap, availables, pl);
    Floor forFloor = readFloor(inputMap, availables, pl);
    Floor fifFloor = readFloor(inputMap, availables, pl);
    cout << firFloor << endl;
    cout << secFloor << endl;
    cout << thiFloor << endl;
    cout << forFloor << endl;
    cout << fifFloor << endl;
}