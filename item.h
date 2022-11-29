#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item
{

public:

    /* Constructors */
    Item(int sku=0, int qty=0, int cents=0, QString name="") :
        sku(sku), qty(qty), cents(cents), name(name) {};

    Item(const Item& i) :
        sku(i.sku), qty(i.qty), cents(i.cents), name(i.name) {};

    int sku;
    int qty;
    int cents;
    QString name;

    bool operator==(const Item&); /* Return whether one Item is equal to another based on ID */
    Item operator=(const Item&); /* Copy assigns the given item */
};

#endif // ITEM_H
