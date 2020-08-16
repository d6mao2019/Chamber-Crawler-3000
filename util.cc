#include "util.h"
#include <stdexcept>

std::istream &operator>>(std::istream &in, Direction &direction)
{
    std::string s;
    in >> s;
    if (s == "no")
        direction = Direction::no;
    else if (s == "so")
        direction = Direction::so;
    else if (s == "we")
        direction = Direction::we;
    else if (s == "ea")
        direction = Direction::ea;
    else if (s == "nw")
        direction = Direction::nw;
    else if (s == "ne")
        direction = Direction::ne;
    else if (s == "sw")
        direction = Direction::sw;
    else if (s == "se")
        direction = Direction::se;
    else
        throw std::runtime_error{"Error: Invalid direction."};
    return in;
}

std::pair<int, int> getNewLoc(int old_row, int old_col, Direction direction)
{
    int new_row;
    int new_col;
    switch (direction)
    {
    case Direction::no:
        new_row = old_row - 1;
        new_col = old_col;
    case Direction::so:
        new_row = old_row + 1;
        new_col = old_col;
    case Direction::we:
        new_row = old_row;
        new_col = old_col - 1;
    case Direction::ea:
        new_row = old_row;
        new_col = old_col + 1;
    case Direction::nw:
        new_row = old_row - 1;
        new_col = old_col - 1;
    case Direction::ne:
        new_row = old_row - 1;
        new_col = old_col + 1;
    case Direction::sw:
        new_row = old_row + 1;
        new_col = old_col - 1;
    case Direction::se:
        new_row = old_row + 1;
        new_col = old_col + 1;
    }
    return std::pair<int, int>{new_row, new_col};
}

std::pair<int, int> getNewLoc(std::pair<int, int> old_location, Direction direction)
{
    int old_row = old_location.first;
    int old_col = old_location.second;
    return getNewLoc(old_row, old_col, direction);
}
