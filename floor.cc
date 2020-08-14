#include "floor.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include <cstdlib>

std::vector<Direction> available_directions(std::shared_ptr<Enemy> e, std::vector<std::vector<char>> &textDisplay)
{
    std::vector<Direction> result;
    int row = e->getRow();
    int col = e->getCol();
    if (textDisplay[row - 1][col] == '.') // north.
        result.push_back(Direction::no);
    if (textDisplay[row + 1][col] == '.') // south.
        result.push_back(Direction::so);
    if (textDisplay[row][col - 1] == '.') // west.
        result.push_back(Direction::we);
    if (textDisplay[row][col + 1] == '.') // east.
        result.push_back(Direction::ea);
    if (textDisplay[row - 1][col - 1] == '.') // north west.
        result.push_back(Direction::nw);
    if (textDisplay[row - 1][col + 1] == '.') // north east.
        result.push_back(Direction::ne);
    if (textDisplay[row + 1][col - 1] == '.') // south west.
        result.push_back(Direction::sw);
    if (textDisplay[row + 1][col + 1] == '.') // south east.
        result.push_back(Direction::se);
    return result;
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
    /* enemy randome moves. */
    if (ERM)
    {
        for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
        {
            std::vector<Direction> availables = available_directions(*i, textDisplay);
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

void Floor::consume_potion(Direction direction)
{
    int row = player->getRow();
    int col = player->getCol();
    /* check if it is a potion. */
    char target;
    switch (direction)
    {
    case Direction::no:
        target = textDisplay[row - 1][col];
    case Direction::so:
        target = textDisplay[row + 1][col];
    case Direction::we:
        target = textDisplay[row][col - 1];
    case Direction::ea:
        target = textDisplay[row][col + 1];
    case Direction::nw:
        target = textDisplay[row - 1][col - 1];
    case Direction::ne:
        target = textDisplay[row - 1][col + 1];
    case Direction::sw:
        target = textDisplay[row + 1][col - 1];
    case Direction::se:
        target = textDisplay[row + 1][col + 1];
    }
    if (target != 'P')
        throw;
    /* find the potion in the list. */
    else
    {
        for (auto i = potion_list.begin(); i != potion_list.end(); ++i)
        {
        }
    }
}
