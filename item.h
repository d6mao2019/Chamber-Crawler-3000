#ifndef ITEM_H
#define ITEM_H
class Item
{
private:
    int row;
    int col;
    const char type;

public:
    Item(char type, int row = 0, int col = 0);
    char getType() const;
    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
};

#endif
