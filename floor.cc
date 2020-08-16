#include "floor.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "potion.h"
#include "gold.h"
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <memory>

std::vector<std::pair<int, int>> available_neighbors(int row, int col, std::vector<std::vector<char>> &text_display)
{
    std::vector<std::pair<int, int>> result;
    if (text_display[row - 1][col] == '.') // north.
        result.emplace_back(row - 1, col);
    if (text_display[row + 1][col] == '.') // south.
        result.emplace_back(row + 1, col);
    if (text_display[row][col - 1] == '.') // west.
        result.emplace_back(row, col - 1);
    if (text_display[row][col + 1] == '.') // east.
        result.emplace_back(row, col + 1);
    if (text_display[row - 1][col - 1] == '.') // north west.
        result.emplace_back(row - 1, col - 1);
    if (text_display[row - 1][col + 1] == '.') // north east.
        result.emplace_back(row - 1, col + 1);
    if (text_display[row + 1][col - 1] == '.') // south west.
        result.emplace_back(row + 1, col - 1);
    if (text_display[row + 1][col + 1] == '.') // south east.
        result.emplace_back(row + 1, col + 1);
    return result;
}

std::vector<Direction> available_directions(std::shared_ptr<Enemy> e, const std::vector<std::vector<char>> &text_display)
{
    std::vector<Direction> result;
    int row = e->getRow();
    int col = e->getCol();
    if (text_display[row - 1][col] == '.') // north.
        result.push_back(Direction::no);
    if (text_display[row + 1][col] == '.') // south.
        result.push_back(Direction::so);
    if (text_display[row][col - 1] == '.') // west.
        result.push_back(Direction::we);
    if (text_display[row][col + 1] == '.') // east.
        result.push_back(Direction::ea);
    if (text_display[row - 1][col - 1] == '.') // north west.
        result.push_back(Direction::nw);
    if (text_display[row - 1][col + 1] == '.') // north east.
        result.push_back(Direction::ne);
    if (text_display[row + 1][col - 1] == '.') // south west.
        result.push_back(Direction::sw);
    if (text_display[row + 1][col + 1] == '.') // south east.
        result.push_back(Direction::se);
    return result;
}

void Floor::select_potion(int row, int col)
{
    int type = rand() % 6;
    std::shared_ptr<Potion> e;
    switch (type)
    {
    case 0:
        e = std::make_shared<HPBoost>(row, col);
        text_display[row][col] = 'P';
        break;
    case 1:
        e = std::make_shared<AtkBoost>(row, col);
        text_display[row][col] = 'P';
        break;
    case 2:
        e = std::make_shared<DefBoost>(row, col);
        text_display[row][col] = 'P';
        break;
    case 3:
        e = std::make_shared<HPWound>(row, col);
        text_display[row][col] = 'P';
        break;
    case 4:
        e = std::make_shared<AtkWound>(row, col);
        text_display[row][col] = 'P';
        break;
    case 5:
        e = std::make_shared<DefWound>(row, col);
        text_display[row][col] = 'P';
        break;
    }
    potion_list.push_back(e);
}

void Floor::select_gold(int row, int col, std::vector<std::pair<int, int>> &avialables)
{
    int type = rand() % 8;
    std::shared_ptr<Gold> g;
    if (0 <= type && type < 5)
    {
        g = std::make_shared<SmallHoard>(row, col);
        text_display[row][col] = 'G';
    }
    else if (5 <= type && type < 6)
    {
        g = std::make_shared<Normal>(row, col);
        text_display[row][col] = 'G';
    }
    else if (6 <= type && type < 8)
    {
        auto gg = std::make_shared<DragonHoard>(row, col);
        g = gg;
        text_display[row][col] = 'G';
        std::vector<std::pair<int, int>> availables = available_neighbors(row, col, text_display);
        std::pair<int, int> location = availables[rand() % availables.size()];
        std::shared_ptr<Dragon> dragon = std::make_shared<Dragon>(location.first, location.second, gg, this);
        enemy_list.push_back(dragon);
        text_display[location.first][location.second] = 'D';
        for (auto i = avialables.begin(); i != avialables.end(); ++i)
        {
            if ((*i).first == location.first && (*i).second == location.second)
            {
                avialables.erase(i);
                break;
            }
        }
    }
    gold_list.push_back(g);
}

void Floor::select_enemy(int row, int col)
{
    int type = rand() % 18;
    if (0 <= type && type < 4) // human.
    {
        auto e = std::make_shared<Human>(row, col, this);
        enemy_list.push_back(e);
        text_display[row][col] = 'H';
    }
    if (4 <= type && type < 7) // dwarf.
    {
        auto e = std::make_shared<Dwarf>(row, col, this);
        enemy_list.push_back(e);
        text_display[row][col] = 'W';
    }
    if (7 <= type && type < 12) // halfling.
    {
        auto e = std::make_shared<Halfling>(row, col, this);
        enemy_list.push_back(e);
        text_display[row][col] = 'L';
    }
    if (12 <= type && type < 14) // elf.
    {
        auto e = std::make_shared<Elf>(row, col, this);
        enemy_list.push_back(e);
        text_display[row][col] = 'E';
    }
    if (14 <= type && type < 16) // orc.
    {
        auto e = std::make_shared<Orc>(row, col, this);
        enemy_list.push_back(e);
        text_display[row][col] = 'O';
    }
    if (16 <= type && type < 18) // merchant.
    {
        auto e = std::make_shared<Merchant>(row, col, this);
        enemy_list.push_back(e);
        text_display[row][col] = 'M';
    }
}

// constructor: does nothing.
Floor::Floor() {}

// constructor: read in locations of characters and items from input.
Floor::Floor(std::vector<std::vector<char>> &text_display,
             std::vector<std::shared_ptr<Enemy>> enemy_list,
             std::vector<std::shared_ptr<Potion>> potion_list,
             std::vector<std::shared_ptr<Gold>> gold_list,
             std::shared_ptr<Player> player,
             std::vector<std::vector<std::pair<int, int>>> &availables)
    : text_display{text_display}, enemy_list{enemy_list}, potion_list{potion_list}, gold_list{gold_list}, player{player}
{
}

// constructor: randomly spawn enemies, potions, and golds.
Floor::Floor(std::vector<std::vector<char>> &td,
             std::shared_ptr<Player> player,
             std::vector<std::vector<std::pair<int, int>>> availables,
             int potion_num, int gold_num, int enemy_num)
    : text_display{td}, player{player}
{
    this->ERM = 1;
    //place player
    std::vector<int> chambers{0, 1, 2, 3, 4};
    int chamber = rand() % chambers.size();
    int index = rand() % availables[chamber].size();
    std::pair<int, int> location = availables[chamber][index];
    availables[chamber].erase(availables[chamber].begin() + index);
    player->setLocation(location.first, location.second);
    text_display[location.first][location.second] = '@';
    // place stairway.
    chambers.erase(chambers.begin() + chamber);
    chamber = chambers[rand() % chambers.size()];
    index = rand() % availables[chamber].size();
    location = availables[chamber][index];
    availables[chamber].erase(availables[chamber].begin() + index);
    text_display[location.first][location.second] = '\\';
    // spawn potion, gold, and enemy.
    for (int i = 0; i < potion_num; ++i)
    {
        int chamber = rand() % 5;
        int index = rand() % availables[chamber].size();
        std::pair<int, int> location = availables[chamber][index];
        select_potion(location.first, location.second);
        availables[chamber].erase(availables[chamber].begin() + index);
    }
    for (int i = 0; i < gold_num; ++i)
    {
        int chamber = rand() % 5;
        int index = rand() % availables[chamber].size();
        std::pair<int, int> location = availables[chamber][index];
        select_gold(location.first, location.second, availables[chamber]);
        availables[chamber].erase(availables[chamber].begin() + index);
    }
    for (int i = 0; i < enemy_num; ++i)
    {
        int chamber = rand() % 5;
        int index = rand() % availables[chamber].size();
        std::pair<int, int> location = availables[chamber][index];
        select_enemy(location.first, location.second);
        availables[chamber].erase(availables[chamber].begin() + index);
    }
}

// copy constructor.
Floor::Floor(const Floor &other)
{
    text_display = other.text_display;
    enemy_list = other.enemy_list;
    for (auto i : enemy_list)
    {
        i->setFloor(this);
    }
    potion_list = other.potion_list;
    gold_list = other.gold_list;
    player = other.player;
    ERM = other.ERM;
}

// copy assign.
void Floor::operator=(const Floor &other)
{
    text_display = other.text_display;
    enemy_list = other.enemy_list;
    for (auto i : enemy_list)
    {
        i->setFloor(this);
    }
    potion_list = other.potion_list;
    gold_list = other.gold_list;
    player = other.player;
    ERM = other.ERM;
}

std::vector<std::vector<char>> Floor::getTextDisplay() const { return text_display; }
bool Floor::getERM() const { return ERM; }
std::shared_ptr<Player> Floor::getPlayer() const { return player; }

void Floor::beNotifiedBy(Enemy &e)
{
    int original_size = enemy_list.size(); // debugging purpose.
    /* modify vector. */
    std::cout << original_size << std::endl;
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        if (**i == e)
        {
            enemy_list.erase(i);
            break;
        }
    }
    if (enemy_list.size() != original_size - 1) // debugging purpose.
        throw std::logic_error{"Bug: something wrong with the enemy list. added or removed improperly sometime."};
    /* modify text display. */
    text_display[e.getRow()][e.getCol()] = '.';
}

void Floor::ERMSwitch()
{
    if (ERM)
        ERM = false;
    else
        ERM = true;
}

void Floor::tick()
{
    /* enemy random moves. */
    if (ERM)
    {
        for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
        {
            char symbol = text_display[(*i)->getRow()][(*i)->getCol()];
            text_display[(*i)->getRow()][(*i)->getCol()] = '.';
            std::vector<Direction> availables = available_directions(*i, text_display);
            Direction direction = availables[rand() % availables.size()];
            (*i)->move(direction);
            text_display[(*i)->getRow()][(*i)->getCol()] = symbol;
        }
    }
    /* enemy attack player. */
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
        player->beAttackedBy(**i);
}

bool Floor::move_player(int old_row, int old_col, int new_row, int new_col)
{
    char target = text_display[new_row][new_col];
    bool move = 0;
    if (target == '.' || target == '+' || target == '#')
        move = 1;
    else if (target == 'G') // want to step onto a Gold.
    {
        for (int i = 0; i < gold_list.size(); i++)
        {
            if (gold_list[i]->cmpLoc(new_row, new_col))
            {
                if (gold_list[i]->canBepickedup())
                {
                    player->setGold(player->getGold() + gold_list[i]->getVal());
                    gold_list.erase(gold_list.begin() + i);
                    move = 1;
                    break;
                }
            }
        }
    }
    else if (target == '\\') // want to goto next floor.
    {
        player->restore();
        return 1;
    }
    else
        throw std::runtime_error{"Error: Trying to move player to an impossible location."};

    if (move)
    {
        player->setLocation(new_row, new_col);
        text_display[old_row][old_col] = player->getPrev();
        text_display[new_row][new_col] = '@';
        player->setPrev(target);
    }
    return 0;
}

void Floor::attack_enemy(Direction direction)
{
    bool success = 0;
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        std::pair<int, int> location = player->GetLocAfterMove(direction, player->getRow(), player->getCol());
        if (location.first == (*i)->getRow() && location.second == (*i)->getCol())
        {
            (*i)->beAttackedBy(*player);
            success = 1;
        }
    }
    if (success == 0)
        throw std::runtime_error{"Error: Specified direction is not an enemy object."};
}

void Floor::consume_potion(Direction direction)
{
    bool success = 0;
    for (auto i = potion_list.begin(); i != potion_list.end(); ++i)
    {
        std::pair<int, int> location = player->GetLocAfterMove(direction, player->getRow(), player->getCol());
        if (location.first == (*i)->getRow() && location.second == (*i)->getCol())
        {
            (*i)->consume(*player);
            potion_list.erase(i);
            text_display[location.first][location.second] = '.';
            success = 1;
        }
    }
    if (success == 0)
        throw std::runtime_error{"Error: Specified direction is not a potion object."};
}

std::ostream &operator<<(std::ostream &out, const Floor &fl)
{
    const std::vector<std::vector<char>> &map = fl.getTextDisplay();
    for (auto i : map)
    {
        for (auto j : i)
        {
            out << j;
        }
        out << std::endl;
    }
    return out;
}
