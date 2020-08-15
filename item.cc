#include "item.h"
Item::Item(const char type, int row, int col)
    : row{row}, col{col}, type{type} {}

char Item::getType() const { return type; }
int Item::getRow() const { return row; }
int Item::getCol() const { return col; }
void Item::setRow(int r) { row = r; }
void Item::setCol(int c) { col = c; }
bool Item::cmpLoc(int r, int c)
{
    return row == r && col == c;
}
