#include "floor.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include "gold.h"

void Floor::select_potion(int row, int col) {}
void Floor::select_gold(int row, int col) {}
void Floor::select_enemy(int row, int col)
{
    int type = rand() % 18;
    if (0 <= type && type < 4) // human.
    {
        auto e = std::make_shared<Human>(row, col);
        enemy_list.push_back(e);
        text_display[row][col] = 'H';
    }
    if (4 <= type && type < 7) // dwarf.
    {
        auto e = std::make_shared<Dwarf>(row, col);
        enemy_list.push_back(e);
        text_display[row][col] = 'W';
    }
    if (7 <= type && type < 12) // halfling.
    {
        auto e = std::make_shared<Halfling>(row, col);
        enemy_list.push_back(e);
        text_display[row][col] = 'L';
    }
    if (12 <= type && type < 14) // elf.
    {
        auto e = std::make_shared<Elf>(row, col);
        enemy_list.push_back(e);
        text_display[row][col] = 'E';
    }
    if (14 <= type && type < 16) // orc.
    {
        auto e = std::make_shared<Orc>(row, col);
        enemy_list.push_back(e);
        text_display[row][col] = 'O';
    }
    if (16 <= type && type < 18) // merchant.
    {
        auto e = std::make_shared<Merchant>(row, col);
        enemy_list.push_back(e);
        text_display[row][col] = 'M';
    }
}
Floor::Floor(std::vector<std::vector<char>> &text_display,
             std::shared_ptr<Player> player,
             std::vector<std::shared_ptr<Enemy>> enemy_list,
             std::vector<std::shared_ptr<Potion>> potion_list,
             std::vector<std::shared_ptr<Gold>> gold_list,
             std::vector<std::vector<std::pair<int, int>>> &availables)
    : text_display{text_display}, player{player}, enemy_list{enemy_list}, potion_list{potion_list}, gold_list{gold_list}
{
    // place player.
    std::vector<int> chambers{0, 1, 2, 3, 4};
    int chamber = rand() % 5;
    std::pair<int, int> location = availables[chamber][rand() % availables[chamber].size()];
    player->setLocation(location.first, location.second);
    // place stairway.
    chambers.erase(chambers.begin() + chamber);
    chamber = chambers[rand() % 4];
    location = availables[chamber][rand() % availables[chamber].size()];
    text_display[location.first][location.second] = '\\';
}
// constructor.
Floor::Floor(std::vector<std::vector<char>> &text_display,
             std::shared_ptr<Player> player,
             std::vector<std::vector<std::pair<int, int>>> &availables,
             int potion_num, int gold_num, int enemy_num)
    : text_display{text_display}, player{player}
{
    this->ERM = 1;
    std::vector<int> chambers{0, 1, 2, 3, 4};
    int chamber = rand() % 5;
    std::pair<int, int> location = availables[chamber][rand() % availables[chamber].size()];
    player->setLocation(location.first, location.second);
    // place stairway.
    chambers.erase(chambers.begin() + chamber);
    chamber = chambers[rand() % 4];
    location = availables[chamber][rand() % availables[chamber].size()];
    text_display[location.first][location.second] = '\\';
    // spawn potion, gold, and enemy.
    std::vector<int> starts{0, 0, 0, 0, 0};
    std::vector<int> nums{potion_num, gold_num, enemy_num};
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < nums[i]; ++j)
        {
            chamber = rand() % 5;
            int start = starts[chamber];
            int rest_len = availables[chamber].size() - start;
            int end = rand() % rest_len + start;
            std::swap(availables[chamber][start], availables[chamber][end]);
            int row = availables[chamber][start].first;
            int col = availables[chamber][start].second;
            if (i == 0)
                select_potion(row, col);
            if (i == 1)
                select_gold(row, col);
            if (i == 2)
                select_enemy(row, col);
            ++starts[chamber];
        }
    }
}

std::vector<std::vector<char>> Floor::getTextDisplay() { return text_display; }

void Floor::beNotifiedBy(Enemy &e)
{
    int original_size = enemy_list.size(); // debugging purpose.
    /* modify vector. */
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        if (**i == e)
            enemy_list.erase(i);
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

// helper.
std::vector<Direction> available_directions(std::shared_ptr<Enemy> e, std::vector<std::vector<char>> &text_display)
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

bool Floor::move_player(int row, int col, int oldRow, int oldCol)
{
    char pos = text_display[row][col];
    bool swap = 0;
    if (pos == '.' || pos == '+' || pos == '#')
    {
        swap = 1;
    }
    else if (pos == 'G')
    {
        for (int i = 0; i < gold_list.size(); i++)
        {
            if (gold_list[i]->cmpLoc(row, col))
            {
                if (gold_list[i]->canBepickedup())
                {
                    player->setGold(player->getGold() + gold_list[i]->getVal());
                    gold_list.erase(gold_list.begin() + i);
                    swap = 1;
                    break;
                }
            }
        }
    }
    else if (pos == '\\')
    {
        player->restore();
        return 1;
    }
    else
    {
        throw std::runtime_error{"Error: trying to move player to an impossible location."};
    }

    if (swap)
    {
        text_display[oldRow][oldCol] = player->getPrev();
        text_display[row][col] = 'P';
        player->setPrev(pos);
    }

    return 0;
}

void Floor::attack_enemy(Direction direction)
{
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
        (*i)->beAttackedBy(*player);
}

void Floor::consume_potion(Direction direction)
{
    for (auto i = potion_list.begin(); i != potion_list.end(); ++i)
    {
        // what to write here depends on implementation of Potion class.
    }
}
