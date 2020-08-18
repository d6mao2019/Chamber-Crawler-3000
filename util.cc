#include "util.h"
#include <stdexcept>

bool is_direction(std::string &s)
{
    return s == "no" || s == "so" || s == "we" || s == "ea" || s == "nw" || s == "ne" || s == "sw" || s == "se";
}

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

std::ostream &operator<<(std::ostream &out, const Direction &direction)
{
    switch (direction)
    {
    case Direction::no:
        out << "north";
        break;
    case Direction::so:
        out << "south";
        break;
    case Direction::we:
        out << "west";
        break;
    case Direction::ea:
        out << "east";
        break;
    case Direction::nw:
        out << "north west";
        break;
    case Direction::ne:
        out << "north east";
        break;
    case Direction::sw:
        out << "south west";
        break;
    case Direction::se:
        out << "south east";
        break;
    }
    return out;
}

std::string getName(Direction direction)
{
    std::string result;
    switch (direction)
    {
    case Direction::no:
        result = "north";
        break;
    case Direction::so:
        result = "south";
        break;
    case Direction::we:
        result = "west";
        break;
    case Direction::ea:
        result = "east";
        break;
    case Direction::nw:
        result = "north west";
        break;
    case Direction::ne:
        result = "north east";
        break;
    case Direction::sw:
        result = "south west";
        break;
    case Direction::se:
        result = "south east";
        break;
    }
    return result;
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
        break;
    case Direction::so:
        new_row = old_row + 1;
        new_col = old_col;
        break;
    case Direction::we:
        new_row = old_row;
        new_col = old_col - 1;
        break;
    case Direction::ea:
        new_row = old_row;
        new_col = old_col + 1;
        break;
    case Direction::nw:
        new_row = old_row - 1;
        new_col = old_col - 1;
        break;
    case Direction::ne:
        new_row = old_row - 1;
        new_col = old_col + 1;
        break;
    case Direction::sw:
        new_row = old_row + 1;
        new_col = old_col - 1;
        break;
    case Direction::se:
        new_row = old_row + 1;
        new_col = old_col + 1;
        break;
    }
    return std::pair<int, int>{new_row, new_col};
}

std::pair<int, int> getNewLoc(std::pair<int, int> old_loc, Direction direction)
{
    return getNewLoc(old_loc.first, old_loc.second, direction);
}
