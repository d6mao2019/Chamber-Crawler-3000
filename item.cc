#include "item.h"
item::item(const char type,int row=0, int col=0)
:row{row},col{col},type{type}
{
}

item::~item()
{
}
