#include "floor.h"
#include "character.h"
#include "enemy.h"
#include <cstdlib>

std::vector<Direction> available_directions(std::shared_ptr<Enemy> e, std::vector<std::vector<char>> &textDisplay)
{
    std::vector<Direction> result;
    int row = e->getRow();
    int col = e->getCol();
    bool north = (textDisplay[row - 1][col] == '.');
    bool south = (textDisplay[row + 1][col] == '.');
    bool west = (textDisplay[row][col - 1] == '.');
    bool east = (textDisplay[row][col + 1] == '.');
    if (north)
        result.push_back(Direction::no);
    if (south)
        result.push_back(Direction::so);
    if (west)
        result.push_back(Direction::we);
    if (east)
        result.push_back(Direction::ea);
    if (north && west)
        result.push_back(Direction::nw);
    if (north && east)
        result.push_back(Direction::ne);
    if (south && west)
        result.push_back(Direction::sw);
    if (south && east)
        result.push_back(Direction::se);
    return result;
}

void Floor::tick()
{
    // enemy randome moves.
    for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
    {
        std::vector<Direction> availables = available_directions(*i, textDisplay);
        Direction direction = availables[rand() % availables.size()];
        (*i)->move(direction);
    }
}
