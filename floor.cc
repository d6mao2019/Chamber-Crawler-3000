#include "floor.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include <cstdlib>
#include <stdexcept>

Floor::Floor(int enemy_num, int positon_num, int gold_num)
{
    /* text_display */
    /* spawn enemies. */
    for (int i = 0; i < enemy_num; ++i)
    {
    }
    /* spawn potions. */
    for (int i = 0; i < positon_num; ++i)
    {
    }
    /* spawn gold piles. */
    for (int i = 0; i < gold_num; ++i)
    {
    }
}

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
    /* enemy randome moves. */
    if (ERM)
    {
        for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
        {
            std::vector<Direction> availables = available_directions(*i, text_display);
            Direction direction = availables[rand() % availables.size()];
            (*i)->move(direction);
        }
    }
    /* enemy attack player. */
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        player->beAttackedBy(**i);
    }
}

void Floor::attack_enemy(Direction direction)
{
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        (*i)->beAttackedBy(*player);
    }
}

void Floor::consume_potion(Direction direction)
{
    for (auto i = potion_list.begin(); i != potion_list.end(); ++i)
    {
    }
}
