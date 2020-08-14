#include "gold.h"

Gold::Gold(int value, int row, int col)
    : value{value}, row{row}, col{col} {}

int Gold::getVal() const { return value; }
int Gold::getRow() const { return row; }
int Gold::getCol() const { return col; }

///////////////////////////////////////////////////////////////////////////////
/* SmallHoard Class */
SmallHoard::SmallHoard(int row, int col)
    : Gold{1, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* Normal Class */
Normal::Normal(int row, int col)
    : Gold{2, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* MerchantHoard Class */
MerchantHoard::MerchantHoard(int row, int col)
    : Gold{4, row, col} {}

///////////////////////////////////////////////////////////////////////////////
/* DragonHoard Class */
DragonHoard::DragonHoard(int row, int col)
    : Gold{6, row, col} {}
