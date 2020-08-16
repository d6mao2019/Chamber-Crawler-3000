#ifndef UTIL_H
#define UTIL_H
#include <iostream>

enum class Direction
{
    no,
    so,
    we,
    ea,
    nw,
    ne,
    sw,
    se
};

std::istream &operator>>(std::istream &in, Direction &direction);
std::ostream &operator<<(std::ostream &out, const Direction &direction);
std::pair<int, int> getNewLoc(int old_row, int old_col, Direction direction);
std::pair<int, int> getNewLoc(std::pair<int, int> old_location, Direction direction);

#endif
