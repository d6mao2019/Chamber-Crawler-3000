#ifndef ITEM_H
#define ITEM_H

class Item
{
private:
    const char type;
    int row;
    int col;

public:
    Item(char type, int row = 0, int col = 0);
    char getType() const;
    int getRow() const;
    int getCol() const;
    void setLocation(int row, int col);
};

#endif // !ITEM_H
