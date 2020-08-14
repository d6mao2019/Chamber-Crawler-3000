#include "item.h"
Item::Item(const char type,int row=0, int col=0)
:row{row},col{col},type{type}
{
}

Item::~Item()
{
}

char Item::getType() const { return type; }
int Item::getRow() const { return row; }
int Item::getCol() const { return col; }
void Item::setRow(int r){ row = r; }
void Item::setCol(int c){ col = c; }
