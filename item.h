#ifndef ITEM_H
#define ITEM_H
#include <QString>

typedef QString qstring;

class Item
{

private:
    qstring id;     // SKU ( ID )
    qstring name;   // Name of item
    int qty;        // Quantity
    int price;      // Price in cents

public:
    /* Constructors */
    Item(qstring id, qstring name, int qty) :
        id(id), name(name), qty(qty) {};

    /* ID Functions */
    qstring getID() const;

    /* Quantity Functions */
    double getQty() const;
    void setQty(int qty);
    void subQty(int qty);
    void addQty(int qty);
};

#endif // ITEM_H

