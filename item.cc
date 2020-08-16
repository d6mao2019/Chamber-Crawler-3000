#include "item.h"
Item::Item(const char type, int row, int col)
    : type{type}, row{row}, col{col} {}

char Item::getType() const { return type; }
int Item::getRow() const { return row; }
int Item::getCol() const { return col; }
void Item::setLocation(int new_row, int new_col)
{
    row = new_row;
    col = new_col;
}
void Item::setRow(int r) { row = r; }
void Item::setCol(int c) { col = c; }
