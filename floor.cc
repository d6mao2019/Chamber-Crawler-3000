#include "floor.h"
#include "character.h"
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
    // enemy randome moves.
    if (ERM)
    {
        for (auto i = enemy_list.begin(); i != enemy_list.end(); ++i)
        {
            std::vector<Direction> availables = available_directions(*i, textDisplay);
            Direction direction = availables[rand() % availables.size()];
            (*i)->move(direction);
        }
    }
}
